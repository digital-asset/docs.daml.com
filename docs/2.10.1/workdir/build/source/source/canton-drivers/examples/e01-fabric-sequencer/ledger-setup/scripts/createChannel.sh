#!/bin/bash

# Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
# Proprietary code. All rights reserved.

# imports
# shellcheck disable=SC1091
. scripts/envVar.sh
. scripts/utils.sh

CHANNEL_NAME="$1"
DELAY="$2"
MAX_RETRY="$3"
VERBOSE="$4"
BFT="$5"
: "${CHANNEL_NAME:="mychannel"}"
: "${DELAY:="3"}"
: "${MAX_RETRY:="5"}"
: "${VERBOSE:="false"}"
: "${BFT:=0}"

if [ ! -d "channel-artifacts" ]; then
  mkdir channel-artifacts
fi

createChannelGenesisBlock() {
  setGlobals 1
  which configtxgen
  if ! which configtxgen; then
    fatalln "configtxgen tool not found."
  fi
  local bft_true=$1
  set -x

  if [ "$bft_true" -eq 1 ]; then
    configtxgen -profile ChannelUsingBFT -outputBlock "./channel-artifacts/${CHANNEL_NAME}.block" -channelID "$CHANNEL_NAME"
  else
    configtxgen -profile TwoOrgsOrdererGenesis -outputBlock "./channel-artifacts/${CHANNEL_NAME}.block" -channelID "$CHANNEL_NAME"
  fi
  res=$?
  { set +x; } 2>/dev/null
  verifyResult $res "Failed to generate channel configuration transaction..."
}
createChannelTx() {

  set -x
  configtxgen -profile TwoOrgsChannel -outputCreateChannelTx "./channel-artifacts/${CHANNEL_NAME}.tx" -channelID "$CHANNEL_NAME"
  res=$?
  set +x
  if [ $res -ne 0 ]; then
    fatalln "Failed to generate channel configuration transaction..."
    exit 1
  fi
  echo

}

createAncorPeerTx() {

  for orgmsp in Org1MSP Org2MSP; do

    infoln "#######    Generating anchor peer update for ${orgmsp}  ##########"
    set -x
    configtxgen -profile TwoOrgsChannel -outputAnchorPeersUpdate ./channel-artifacts/${orgmsp}anchors.tx -channelID "$CHANNEL_NAME" -asOrg ${orgmsp}
    res=$?
    set +x
    if [ $res -ne 0 ]; then
      infoln "Failed to generate anchor peer update for ${orgmsp}..."
      exit 1
    fi
    echo
  done
}

createChannel() {
  setOrdererGlobals
  # Poll in case the raft leader is not set yet
  local rc=1
  local COUNTER=1
  while [ $rc -ne 0 ] && [ $COUNTER -lt "$MAX_RETRY" ]; do
    if [ $COUNTER -gt 1 ]; then sleep "$DELAY"; fi
    set -x
    peer channel create \
      -o orderer.example.com:7050 \
      -c "$CHANNEL_NAME" --ordererTLSHostnameOverride orderer.example.com \
      -f "./channel-artifacts/${CHANNEL_NAME}.tx" \
      --outputBlock "./channel-artifacts/${CHANNEL_NAME}.block" \
      --tls "$CORE_PEER_TLS_ENABLED" \
      --cafile "$ORDERER_CA" \
      >&log.txt
    res=$?
    set +x
    ((rc = res))
    COUNTER=$((COUNTER + 1))
  done
  cat log.txt
  verifyResult $res "Channel creation failed"
}

# joinChannel ORG
joinChannel() {
  ORG=$1
  FABRIC_CFG_PATH=$PWD/config/
  setGlobals "$ORG"
  local rc=1
  local COUNTER=1
  ## Sometimes Join takes time, hence retry
  while [ $rc -ne 0 ] && [ "$COUNTER" -lt "$MAX_RETRY" ]; do
    sleep "$DELAY"
    set -x
    peer channel join -b "$BLOCKFILE" >&log.txt
    res=$?
    { set +x; } 2>/dev/null
    ((rc = res))
    COUNTER=$((COUNTER + 1))
  done
  cat log.txt
  verifyResult $res "After $MAX_RETRY attempts, peer0.org${ORG} has failed to join channel '$CHANNEL_NAME' "
}

setAnchorPeer() {
  ORG=$1
  setGlobals "$ORG"
  local rc=1
  local COUNTER=1
  ## Sometimes Join takes time, hence retry
  while [ $rc -ne 0 ] && [ $COUNTER -lt "$MAX_RETRY" ]; do
    if [ $COUNTER -gt 1 ]; then sleep "$DELAY"; fi
    set -x
    peer channel update \
      -o orderer.example.com:7050 \
      --ordererTLSHostnameOverride orderer.example.com \
      -c "$CHANNEL_NAME" \
      -f "./channel-artifacts/${CORE_PEER_LOCALMSPID}anchors.tx" \
      --tls "$CORE_PEER_TLS_ENABLED" \
      --cafile "$ORDERER_CA" \
      >&log.txt
    res=$?
    set +x
    ((rc = res))
    COUNTER=$((COUNTER + 1))
  done
  cat log.txt
  verifyResult $res "Anchor peer update failed"
  infoln "===================== Anchor peers updated for org '$CORE_PEER_LOCALMSPID' on channel '$CHANNEL_NAME' ===================== "
}

## User attempts to use BFT orderer in Fabric network with CA
if [ "$BFT" -eq 1 ] && [ -d "organizations/fabric-ca/ordererOrg/msp" ]; then
  fatalln "Fabric network seems to be using CA. This sample does not yet support the use of consensus type BFT and CA together."
fi

## Create channel genesis block
FABRIC_CFG_PATH=$PWD/config/
BLOCKFILE="./channel-artifacts/${CHANNEL_NAME}.block"
export BLOCKFILE

infoln "Generating channel genesis block '${CHANNEL_NAME}.block'"
FABRIC_CFG_PATH=${PWD}/configtx
if [ "$BFT" -eq 1 ]; then
  FABRIC_CFG_PATH=${PWD}/bft-config
fi
export FABRIC_CFG_PATH
createChannelGenesisBlock "$BFT"

## Create channeltx
infoln "### Generating channel configuration transaction '${CHANNEL_NAME}.tx' ###"
createChannelTx

## Create anchorpeertx
infoln "### Generating channel configuration transaction '${CHANNEL_NAME}.tx' ###"
createAncorPeerTx

## Create channel
infoln "Creating channel ${CHANNEL_NAME}"
createChannel "$BFT"
successln "Channel '$CHANNEL_NAME' created"

## Join all the peers to the channel
infoln "Joining org1 peer to the channel..."
joinChannel 1
infoln "Joining org2 peer to the channel..."
joinChannel 2

## Set the anchor peers for each org in the channel
infoln "Setting anchor peer for org1..."
setAnchorPeer 1
infoln "Setting anchor peer for org2..."
setAnchorPeer 2

successln "Channel '$CHANNEL_NAME' joined"
