#!/usr/bin/env bash
# Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
# Proprietary code. All rights reserved.

set -Eeuo pipefail

rm -f log.txt

# Print the usage message
function printHelp() {
  cat <<-HeredocDelimiter
		Usage:
		  run.sh <Mode> [Flags]
		    <Mode>
		      - 'full' - starts full canton setup with 2 fabric sequencers
		      - 'ledger' - only starts the Fabric ledger without starting canton
		      - 'down' - stops and cleans up the running setup
		    Flags:
		    -e <block explorer> - spin up blockchain explorer (will be available on localhost:8080)
		  run.sh -h (print this message)
		 Possible Mode and flags
		  run.sh full -e
		  run.sh ledger -e
		  run.sh down
		HeredocDelimiter
}

absdir="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)" # get the full path to the directory where this script is

## Parse mode
if [[ $# -lt 1 ]]; then
  printHelp
  exit 0
else
  MODE=$1
  shift
fi

# Check if the image exists
if [ "$MODE" != "full" ]; then
  echo "Mode is not 'full'. Skipping image check and pull."
elif [ -n "${CANTON_IMAGE:-}" ]; then
  if ! docker image inspect "$CANTON_IMAGE":"$CANTON_VERSION" >/dev/null 2>&1; then
    echo "Warn: $CANTON_IMAGE:$CANTON_VERSION image does not exist locally"
    # Try to pull the image
    if docker image pull "$CANTON_IMAGE":"$CANTON_VERSION"; then
      echo "Image pulled successfully."
    else
      echo "Error: failed to pull $CANTON_IMAGE:$CANTON_VERSION image"
      exit 1
    fi
  fi
fi

EXPLORER=false

while [[ $# -ge 1 ]]; do
  key="$1"
  case $key in
    -h)
      printHelp
      exit 0
      ;;
    -e)
      EXPLORER=true
      echo "Block explorer will be started on localhost:8080"
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
done

LEDGER_COMPOSE_FILE="$absdir/docker-compose-ledger.yaml"
CANTON_COMPOSE_FILE="$absdir/docker-compose-canton.yaml"
EXPLORER_COMPOSE_FILE="$absdir/docker-compose-blockchain-explorer.yaml"

# Docker Compose CLI environment variable: same as specifying -p flag
# Will affect all docker compose commands in this file
export COMPOSE_PROJECT_NAME="fabric-sequencer-demo"
# Note that similarly, COMPOSE_FILE is used in the functions below as a Docker Compose CLI environment variable
# in order to define which docker compose files to use, same as specifying -f flag multiple times with each file

function runLedger() {
  down
  export COMPOSE_FILE="$LEDGER_COMPOSE_FILE"
  run
}

function runFullSetup() {
  down

  COMPOSE_FILE="$LEDGER_COMPOSE_FILE:$CANTON_COMPOSE_FILE"

  run
}

function down() {
  # use all docker compose files to make sure to stop containers from any combination of compose files
  export COMPOSE_FILE="$LEDGER_COMPOSE_FILE:$CANTON_COMPOSE_FILE:$EXPLORER_COMPOSE_FILE"
  docker compose down -v
  cleanupDanglingChaincodeImages
}

# clean up any dangling Chaincode container and images from past runs
function cleanupDanglingChaincodeImages() {
  echo "Cleaning dangling Chaincode images"
  set +e

  lines=$(docker ps -a | grep -c 'dev-peer')

  if [[ $lines -gt 0 ]]; then
    docker ps -a | grep 'dev-peer' | awk '{print $1}' | xargs docker rm -f
  fi

  lines=$(docker images "dev-peer*" -q | wc -l)

  if [[ $lines -gt 0 ]]; then
    docker rmi "$(docker images "dev-peer*" -q)"
  fi
  set -e
}

function run() {
  if [[ $EXPLORER == true ]]; then
    export COMPOSE_FILE="$COMPOSE_FILE:$EXPLORER_COMPOSE_FILE"
  fi
  USER_ID=$(id -u)
  export USER_ID
  GROUP_ID=$(id -g)
  export GROUP_ID
  docker compose up --force-recreate --always-recreate-deps --build 2>&1 | tee -a log.txt
}

if [ "${MODE}" == "full" ]; then
  runFullSetup
elif [ "${MODE}" == "ledger" ]; then
  runLedger
elif [ "${MODE}" == "down" ]; then
  down
else
  printHelp
  exit 1
fi
