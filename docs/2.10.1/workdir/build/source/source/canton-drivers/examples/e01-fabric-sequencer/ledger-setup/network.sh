#!/bin/bash
#
# Copyright IBM Corp All Rights Reserved
#
# SPDX-License-Identifier: Apache-2.0
#

# This script brings up a Hyperledger Fabric network for testing smart contracts
# and applications. The test network consists of two organizations with one
# peer each, and a single node Raft ordering service. Users can also use this
# script to create a channel deploy a chaincode on the channel
#
# prepending $PWD/../bin to PATH to ensure we are picking up the correct binaries
# this may be commented out to resolve installed version of tools if desired
# export PATH=${PWD}/../bin:${PWD}:$PATH
export FABRIC_CFG_PATH=${PWD}/configtx
export VERBOSE=false

# Print the usage message
function printHelp() {
  echo "Usage: "
  echo "  network.sh <Mode> [Flags]"
  echo "    <Mode>"
  echo "      - 'createCrypto' - creates crypto materials"
  echo "      - 'createChannel' - create and join a channel after the network is created"
  echo "      - 'deployCC' - deploy the chaincode on the channel"
  echo "      - 'deploy' - create and join a channel and deploy the chaincode on the channel. Allows creating multiple channels with the n flag."
  echo
  echo "    Flags:"
  echo '    -c <channel name> - channel name to use (defaults to "mychannel")'
  echo "    -n <number of channels> - in order to create multiple channels, define this arg. Only works with the 'deploy' command. The given channel name will be used as a prefix, and the actual channels created will be suffixed with counters starting from 1."
  echo "    -r <max retry> - CLI times out after certain number of attempts (defaults to 5)"
  echo "    -d <delay> - delay duration in seconds (defaults to 3)"
  echo "    -l <language> - the programming language of the chaincode to deploy: go (default), java, javascript, typescript"
  echo "    -v <version>  - chaincode version. Must be a round number, 1, 2, 3, etc"
  echo "    -verbose - verbose mode"
  echo "  network.sh -h (print this message)"
  echo
  echo " Possible Mode and flags"
  echo "  network.sh createChannel -c -r -d -verbose"
  echo "  network.sh deployCC -l -v -r -d -verbose"
  echo
  echo " Examples:"
  echo "  network.sh up createChannel -c mychannel -s couchdb -i 2.0.0"
  echo "  network.sh createChannel -c channelName"
  echo "  network.sh deployCC"
}

function checkPrereqs() {
  ## Check if your have cloned the peer binaries and configuration files.
  if ! peer version >/dev/null 2>&1 || [[ ! -d "config" ]]; then
    echo "ERROR! Peer binary and configuration files not found.."
    echo
    echo "Follow the instructions in the Fabric docs to install the Fabric Binaries:"
    echo "https://hyperledger-fabric.readthedocs.io/en/latest/install.html"
    exit 1
  fi
}

# Before you can bring up a network, each organization needs to generate the crypto
# material that will define that organization on the network. Because Hyperledger
# Fabric is a permissioned blockchain, each node and user on the network needs to
# use certificates and keys to sign and verify its actions. In addition, each user
# needs to belong to an organization that is recognized as a member of the network.
# You can use the Cryptogen tool or Fabric CAs to generate the organization crypto
# material.

# By default, the sample network uses cryptogen. Cryptogen is a tool that is
# meant for development and testing that can quicky create the certificates and keys
# that can be consumed by a Fabric network. The cryptogen tool consumes a series
# of configuration files for each organization in the "config/cryptogen"
# directory. Cryptogen uses the files to generate the crypto  material for each
# org in the "organizations" directory.

# You can also Fabric CAs to generate the crypto material. CAs sign the certificates
# and keys that they generate to create a valid root of trust for each organization.
# The script uses Docker Compose to bring up three CAs, one for each peer organization
# and the ordering organization. The configuration file for creating the Fabric CA
# servers are in the "organizations/fabric-ca" directory. Within the same diectory,
# the "registerEnroll.sh" script uses the Fabric CA client to create the identites,
# certificates, and MSP folders that are needed to create the test network in the
# "organizations/ordererOrganizations" directory.

# Create Organziation crypto material using cryptogen or CAs
function createOrgs() {

  if [ -d "organizations/peerOrganizations" ]; then
    rm -Rf organizations/peerOrganizations && rm -Rf organizations/ordererOrganizations
  fi

  # Create crypto material using cryptogen
  if ! which cryptogen; then
    echo "cryptogen tool not found. exiting"
    exit 1
  fi
  echo
  echo "##########################################################"
  echo "##### Generate certificates using cryptogen tool #########"
  echo "##########################################################"
  echo

  echo "##########################################################"
  echo "############ Create Org1 Identities ######################"
  echo "##########################################################"

  set -x
  cryptogen generate --config=./config/cryptogen/crypto-config-org1.yaml --output="organizations"
  res=$?
  set +x
  if [ $res -ne 0 ]; then
    echo "Failed to generate certificates..."
    exit 1
  fi

  echo "##########################################################"
  echo "############ Create Org2 Identities ######################"
  echo "##########################################################"

  set -x
  cryptogen generate --config=./config/cryptogen/crypto-config-org2.yaml --output="organizations"
  res=$?
  set +x
  if [ $res -ne 0 ]; then
    echo "Failed to generate certificates..."
    exit 1
  fi

  echo "##########################################################"
  echo "############ Create Orderer Org Identities ###############"
  echo "##########################################################"

  set -x
  cryptogen generate --config=./config/cryptogen/crypto-config-orderer.yaml --output="organizations"
  res=$?
  set +x
  if [ $res -ne 0 ]; then
    echo "Failed to generate certificates..."
    exit 1
  fi
}

# Once you create the organization crypto material, you need to create the
# genesis block of the orderer system channel. This block is required to bring
# up any orderer nodes and create any application channels.

# The configtxgen tool is used to create the genesis block. Configtxgen consumes a
# "configtx.yaml" file that contains the definitions for the sample network. The
# genesis block is defiend using the "TwoOrgsOrdererGenesis" profile at the bottom
# of the file. This profile defines a sample consortium, "SampleConsortium",
# consisting of our two Peer Orgs. This consortium defines which organizations are
# recognized as members of the network. The peer and ordering organizations are defined
# in the "Profiles" section at the top of the file. As part of each organization
# profile, the file points to a the location of the MSP directory for each member.
# This MSP is used to create the channel MSP that defines the root of trust for
# each organization. In essense, the channel MSP allows the nodes and users to be
# recognized as network members. The file also specifies the anchor peers for each
# peer org. In future steps, this same file is used to create the channel creation
# transaction and the anchor peer updates.
#
#
# If you receive the following warning, it can be safely ignored:
#
# [bccsp] GetDefault -> WARN 001 Before using BCCSP, please call InitFactories(). Falling back to bootBCCSP.
#
# You can ignore the logs regarding intermediate certs, we are not using them in
# this crypto implementation.

# Generate orderer system channel genesis block.
function createConsortium() {

  if ! which configtxgen; then
    echo "configtxgen tool not found. exiting"
    exit 1
  fi

  echo "#########  Generating Orderer Genesis block ##############"

  # Note: For some unknown reason (at least for now) the block file can't be
  # named orderer.genesis.block or the orderer will fail to launch!
  set -x
  configtxgen -profile TwoOrgsOrdererGenesis -channelID system-channel -outputBlock ./system-genesis-block/genesis.block
  res=$?
  set +x
  if [ $res -ne 0 ]; then
    echo "Failed to generate orderer genesis block..."
    exit 1
  fi
}

# After we create the org crypto material and the system channel genesis block,
# we can now bring up the peers and orderering service. By default, the base
# file for creating the network is "docker-compose-test-net.yaml" in the ``docker``
# folder. This file defines the environment variables and file mounts that
# point the crypto material and genesis block that were created in earlier.

function createCryptoMaterial() {
  checkPrereqs
  # generate artifacts
  createOrgs
  createConsortium
}

## call the script to join create the channel and join the peers of org1 and org2
function createChannel() {

  ## Bring up the network if it is not arleady up.

  if [ ! -d "organizations/peerOrganizations" ]; then
    echo "Bringing up network"
    networkUp
  fi

  channelName=$1
  # now run the script that creates a channel. This script uses configtxgen once
  # more to create the channel creation transaction and the anchor peer updates.
  # configtx.yaml is mounted in the cli container, which allows us to use it to
  # create the channel artifacts
  if ! scripts/createChannel.sh "$channelName" "$CLI_DELAY" "$MAX_RETRY" $VERBOSE; then
    echo "Error !!! Create channel failed"
    exit 1
  fi

}

## Call the script to install and instantiate a chaincode on the channel
function deployCC() {
  channelName=$1
  installOnPeer=${2:-true}

  if ! scripts/deployCC.sh "$channelName" "$CC_SRC_LANGUAGE" "$VERSION" "$CLI_DELAY" "$MAX_RETRY" $VERBOSE "$installOnPeer"; then
    echo "ERROR !!! Deploying chaincode failed"
    exit 1
  fi
}

function deploy() {
  if [ "$NUMBER_OF_CHANNELS" -gt 1 ]; then
    for ((i = 1; i <= NUMBER_OF_CHANNELS; i++)); do
      # if we're creating multiple channels, add a counter suffix to each
      local channelNameWithCounter="$CHANNEL_NAME$i"
      createChannel "$channelNameWithCounter"
      # the first time we're deploying chaincode on a channel, we want to install it on peers.
      # from the second channel onwards, we want to skip that step since it only needs to happen once.
      # so we signal that here with this flag.
      [[ $i == 1 ]] && firstChaincodeDeploy="true" || firstChaincodeDeploy="false"
      deployCC "$channelNameWithCounter" "$firstChaincodeDeploy"
    done
  else
    createChannel "$CHANNEL_NAME"
    deployCC "$CHANNEL_NAME"
  fi
}

# Using crpto vs CA. default is cryptogen
CRYPTO="cryptogen"
# timeout duration - the duration the CLI should wait for a response from
# another container before giving up
MAX_RETRY=5
# default for delay between commands
CLI_DELAY=3
# number of channels to create if calling deploy
NUMBER_OF_CHANNELS=1
# channel name defaults to "mychannel"
CHANNEL_NAME="mychannel"
# use golang as the default language for chaincode
CC_SRC_LANGUAGE=golang
# Chaincode version
VERSION=1

# Parse commandline args

## Parse mode
if [[ $# -lt 1 ]]; then
  printHelp
  exit 0
else
  MODE=$1
  shift
fi

# parse a createChannel subcommand if used
if [[ $# -ge 1 ]]; then
  key="$1"
  if [[ $key == "createChannel" ]]; then
    export MODE="createChannel"
    shift
  fi
fi

# parse flags

while [[ $# -ge 1 ]]; do
  key="$1"
  case $key in
    -h)
      printHelp
      exit 0
      ;;
    -c)
      CHANNEL_NAME="$2"
      shift
      ;;
    -n)
      NUMBER_OF_CHANNELS="$2"
      shift
      ;;
    -r)
      MAX_RETRY="$2"
      shift
      ;;
    -d)
      CLI_DELAY="$2"
      shift
      ;;
    -l)
      CC_SRC_LANGUAGE="$2"
      shift
      ;;
    -v)
      VERSION="$2"
      shift
      ;;
    -verbose)
      VERBOSE=true
      shift
      ;;
    *)
      echo
      echo "Unknown flag: $key"
      echo
      printHelp
      exit 1
      ;;
  esac
  shift
done

# Are we generating crypto material with this command?
if [ ! -d "organizations/peerOrganizations" ]; then
  CRYPTO_MODE="with crypto from '${CRYPTO}'"
else
  CRYPTO_MODE=""
fi

# Determine mode of operation and printing out what we asked for
if [ "$MODE" == "createCrypto" ]; then
  echo "Creating crypto material ${CRYPTO_MODE}"
  echo
elif [ "$MODE" == "createChannel" ]; then
  echo "Creating channel '${CHANNEL_NAME}'."
  echo
  echo "If network is not up, starting nodes with CLI timeout of '${MAX_RETRY}' tries and CLI delay of '${CLI_DELAY}' seconds and using ${CRYPTO_MODE}"
  echo
elif [ "$MODE" == "deployCC" ]; then
  echo "deploying chaincode on channel '${CHANNEL_NAME}'"
  echo
elif [ "$MODE" == "deploy" ]; then
  if [ "$NUMBER_OF_CHANNELS" -gt 1 ]; then
    echo "Creating $NUMBER_OF_CHANNELS channels with '${CHANNEL_NAME}' prefix and deploying chaincode."
  else
    echo "Creating channel '${CHANNEL_NAME}' and deploying chaincode."
  fi
  echo
  echo "If network is not up, starting nodes with CLI timeout of '${MAX_RETRY}' tries and CLI delay of '${CLI_DELAY}' seconds and using ${CRYPTO_MODE}"
  echo
else
  printHelp
  exit 1
fi

if [ "${MODE}" == "createCrypto" ]; then
  createCryptoMaterial
elif [ "${MODE}" == "createChannel" ]; then
  createChannel "$CHANNEL_NAME"
elif [ "${MODE}" == "deployCC" ]; then
  deployCC "$CHANNEL_NAME"
elif [ "${MODE}" == "deploy" ]; then
  deploy
else
  printHelp
  exit 1
fi
