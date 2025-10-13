#!/bin/bash

# Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
# Proprietary code. All rights reserved.

CHANNEL_NAME="$1"
CC_SRC_LANGUAGE="$2"
export CC_SRC_LANGUAGE
VERSION="$3"
DELAY="$4"
MAX_RETRY="$5"
VERBOSE="$6"
INSTALL_ON_PEER="$7"
: "${VERSION:="1"}"
: "${DELAY:="3"}"
: "${MAX_RETRY:="5"}"
: "${VERBOSE:="false"}"
: "${INSTALL_ON_PEER:="true"}"

FABRIC_CFG_PATH=$PWD/config/
export FABRIC_CFG_PATH

CC_RUNTIME_LANGUAGE=golang
if [ -z "$CC_SRC_PATH" ]; then
  CC_SRC_PATH="/opt/ledger-setup/chaincode/src/github.com/digital-asset/sequencer"
fi
CC_COLLECTIONS_CONFIG_PATH="$CC_SRC_PATH/collections_config.json"
CC_NAME="sequencer"

# the hash is used so that we can detect that the chaincode has changed and repackage it
cc_hash=$(cd "$CC_SRC_PATH" && cat -- * | sha256sum | head -c 10)
if [ -z "$CC_PACKAGE_DIR" ]; then
  CC_PACKAGE_DIR="/opt/ledger-setup/chaincode-package"
fi
CC_PACKAGE="${CC_PACKAGE_DIR}/${CC_NAME}-${cc_hash}.tar.gz"

echo Vendoring Go dependencies ...
pushd "$CC_SRC_PATH" || exit
GO111MODULE=on go mod vendor
popd || exit
echo Finished vendoring Go dependencies

# import utils
# shellcheck disable=SC1091
. scripts/envVar.sh

packageChaincode() {
  ORG=$1
  setGlobals "$ORG"
  set -x
  peer lifecycle chaincode package "${CC_PACKAGE}" --path "${CC_SRC_PATH}" --lang ${CC_RUNTIME_LANGUAGE} --label "${CC_NAME}_${VERSION}" >&log.txt
  res=$?
  set +x
  cat log.txt
  verifyResult $res "Chaincode packaging on peer0.org${ORG} has failed"
  echo "===================== Chaincode is packaged on peer0.org${ORG} ===================== "
  echo
}

# installChaincode PEER ORG
installChaincode() {
  ORG=$1
  setGlobals "$ORG"
  set -x
  peer lifecycle chaincode install "${CC_PACKAGE}" >&log.txt
  res=$?
  set +x
  cat log.txt
  verifyResult $res "Chaincode installation on peer0.org${ORG} has failed"
  echo "===================== Chaincode is installed on peer0.org${ORG} ===================== "
  echo
}

# queryInstalled PEER ORG
queryInstalled() {
  ORG=$1
  setGlobals "$ORG"
  set -x
  peer lifecycle chaincode queryinstalled >&log.txt
  res=$?
  set +x
  cat log.txt
  PACKAGE_ID=$(sed -n "/${CC_NAME}_${VERSION}/{s/^Package ID: //; s/, Label:.*$//; p;}" log.txt)
  verifyResult $res "Query installed on peer0.org${ORG} has failed"
  echo PackageID is "${PACKAGE_ID}"
  echo "===================== Query installed successful on peer0.org${ORG} on channel ===================== "
  echo
}

# approveForMyOrg VERSION PEER ORG
approveForMyOrg() {
  ORG=$1
  setGlobals "$ORG"
  set -x

  peer lifecycle chaincode approveformyorg \
    -o orderer.example.com:7050 \
    --ordererTLSHostnameOverride orderer.example.com \
    --tls "$CORE_PEER_TLS_ENABLED" \
    --cafile "$ORDERER_CA" \
    --channelID "$CHANNEL_NAME" \
    --name $CC_NAME \
    --collections-config "${CC_COLLECTIONS_CONFIG_PATH}" \
    --version "${VERSION}" \
    --init-required \
    --package-id "${PACKAGE_ID}" \
    --sequence "${VERSION}" \
    >&log.txt
  set +x
  cat log.txt
  verifyResult $res "Chaincode definition approved on peer0.org${ORG} on channel '$CHANNEL_NAME' failed"
  echo "===================== Chaincode definition approved on peer0.org${ORG} on channel '$CHANNEL_NAME' ===================== "
  echo
}

# checkCommitReadiness VERSION PEER ORG
checkCommitReadiness() {
  ORG=$1
  shift 1
  setGlobals "$ORG"
  echo "===================== Checking the commit readiness of the chaincode definition on peer0.org${ORG} on channel '$CHANNEL_NAME'... ===================== "
  local rc=1
  local COUNTER=1
  # continue to poll
  # we either get a successful response, or reach MAX RETRY
  while [ $rc -ne 0 ] && [ $COUNTER -lt "$MAX_RETRY" ]; do
    if [ $COUNTER -gt 1 ]; then sleep "$DELAY"; fi
    echo "Attempting to check the commit readiness of the chaincode definition on peer0.org${ORG} secs"
    set -x
    peer lifecycle chaincode checkcommitreadiness \
      --channelID "$CHANNEL_NAME" \
      --name ${CC_NAME} \
      --collections-config "${CC_COLLECTIONS_CONFIG_PATH}" \
      --version "${VERSION}" \
      --sequence "${VERSION}" \
      --output json \
      --init-required \
      >&log.txt
    res=$?
    set +x
    ((rc = 0))
    for var in "$@"; do
      grep "$var" log.txt &>/dev/null || ((rc = 1))
    done
    COUNTER=$((COUNTER + 1))
  done
  cat log.txt
  if test "$rc" -eq 0; then
    echo "===================== Checking the commit readiness of the chaincode definition successful on peer0.org${ORG} on channel '$CHANNEL_NAME' ===================== "
  else
    echo "!!!!!!!!!!!!!!! After $MAX_RETRY attempts, Check commit readiness result on peer0.org${ORG} is INVALID !!!!!!!!!!!!!!!!"
    echo
    exit 1
  fi
}

# commitChaincodeDefinition VERSION PEER ORG (PEER ORG)...
commitChaincodeDefinition() {
  parsePeerConnectionParameters "$@"
  res=$?
  verifyResult $res "Invoke transaction failed on channel '$CHANNEL_NAME' due to uneven number of peer and org parameters "
  # while 'peer chaincode' command can get the orderer endpoint from the
  # peer (if join was successful), let's supply it directly as we know
  # it using the "-o" option
  set -x
  # this command relies of word splitting
  # shellcheck disable=SC2086
  peer lifecycle chaincode commit \
    -o orderer.example.com:7050 \
    --ordererTLSHostnameOverride orderer.example.com \
    --tls "$CORE_PEER_TLS_ENABLED" \
    --cafile "$ORDERER_CA" \
    --channelID "$CHANNEL_NAME" \
    --name ${CC_NAME} \
    --collections-config ${CC_COLLECTIONS_CONFIG_PATH} \
    $PEER_CONN_PARMS \
    --version ${VERSION} \
    --sequence ${VERSION} \
    --init-required \
    >&log.txt
  res=$?
  set +x
  cat log.txt
  verifyResult $res "Chaincode definition commit failed on peer0.org${ORG} on channel '$CHANNEL_NAME' failed"
  echo "===================== Chaincode definition committed on channel '$CHANNEL_NAME' ===================== "
  echo
}

# queryCommitted ORG
queryCommitted() {
  ORG=$1
  setGlobals "$ORG"
  EXPECTED_RESULT="Version: ${VERSION}, Sequence: ${VERSION}, Endorsement Plugin: escc, Validation Plugin: vscc"
  echo "===================== Querying chaincode definition on peer0.org${ORG} on channel '$CHANNEL_NAME'... ===================== "
  local rc=1
  local COUNTER=1
  # continue to poll
  # we either get a successful response, or reach MAX RETRY
  while [ $rc -ne 0 ] && [ $COUNTER -lt "$MAX_RETRY" ]; do
    if [ $COUNTER -gt 1 ]; then sleep "$DELAY"; fi
    echo "Attempting to Query committed status on peer0.org${ORG}, Retry after $DELAY seconds."
    set -x
    peer lifecycle chaincode querycommitted \
      --channelID "$CHANNEL_NAME" \
      --name ${CC_NAME} \
      --clientauth "$CORE_PEER_TLS_CLIENTAUTHREQUIRED" \
      --certfile "$CLIENT_CERT_FILE" \
      --keyfile "$CLIENT_KEY_FILE" \
      >&log.txt
    res=$?
    set +x
    test $res -eq 0 && VALUE=$(grep -o '^Version: [0-9], Sequence: [0-9], Endorsement Plugin: escc, Validation Plugin: vscc' log.txt)
    test "$VALUE" = "$EXPECTED_RESULT" && ((rc = 0))
    COUNTER=$((COUNTER + 1))
  done
  echo
  cat log.txt
  if test "$rc" -eq 0; then
    echo "===================== Query chaincode definition successful on peer0.org${ORG} on channel '$CHANNEL_NAME' ===================== "
    echo
  else
    echo "!!!!!!!!!!!!!!! After $MAX_RETRY attempts, Query chaincode definition result on peer0.org${ORG} is INVALID !!!!!!!!!!!!!!!!"
    echo
    exit 1
  fi
}

chaincodeInvokeInit() {
  parsePeerConnectionParameters "$@"
  res=$?
  verifyResult $res "Invoke transaction failed on channel '$CHANNEL_NAME' due to uneven number of peer and org parameters "

  # while 'peer chaincode' command can get the orderer endpoint from the
  # peer (if join was successful), let's supply it directly as we know
  # it using the "-o" option
  set -x
  # this command relies of word splitting
  # shellcheck disable=SC2086
  peer chaincode invoke \
    -o orderer.example.com:7050 \
    --ordererTLSHostnameOverride orderer.example.com \
    --tls "$CORE_PEER_TLS_ENABLED" \
    --cafile "$ORDERER_CA" \
    -C "$CHANNEL_NAME" \
    -n ${CC_NAME} \
    $PEER_CONN_PARMS \
    --isInit \
    -c '{"function":"init","Args":[]}' \
    >&log.txt
  res=$?
  set +x
  cat log.txt
  verifyResult $res "Invoke execution on $PEERS failed "
  echo "===================== Invoke transaction successful on $PEERS on channel '$CHANNEL_NAME' ===================== "
  echo
}

## at first we package the chaincode (if it hasn't already been packaged)
if [ -f "$CC_PACKAGE" ]; then
  echo "Chaincode package $CC_PACKAGE has already been cached. Skipping chaincode packaging"
else
  echo "Packaging chaincode..."
  set -u
  mkdir -p "${CC_PACKAGE_DIR}"
  # delete previous outdated package files (in case chaincode has changed)
  rm -f "${CC_PACKAGE_DIR}"/*
  set +u
  packageChaincode 1
fi

if [ "${INSTALL_ON_PEER}" == "true" ]; then
  ## Install chaincode on peer0.org1 and peer0.org2
  echo "Installing chaincode on peer0.org1..."
  installChaincode 1
  echo "Install chaincode on peer0.org2..."
  installChaincode 2
fi

## query whether the chaincode is installed
queryInstalled 1

## approve the definition for org1
approveForMyOrg 1

## check whether the chaincode definition is ready to be committed
## expect org1 to have approved and org2 not to
checkCommitReadiness 1 '"Org1MSP": true' '"Org2MSP": false'
checkCommitReadiness 2 '"Org1MSP": true' '"Org2MSP": false'

## now approve also for org2
approveForMyOrg 2

## check whether the chaincode definition is ready to be committed
## expect them both to have approved
checkCommitReadiness 1 '"Org1MSP": true' '"Org2MSP": true'
checkCommitReadiness 2 '"Org1MSP": true' '"Org2MSP": true'

## now that we know for sure both orgs have approved, commit the definition
commitChaincodeDefinition 1 2

## query on both orgs to see that the definition committed successfully
queryCommitted 1
queryCommitted 2

## Invoke the chaincode
chaincodeInvokeInit 1 2

echo
echo "===================== Chaincode $CC_NAME deployment on $CHANNEL_NAME complete! ====================="
echo

exit 0
