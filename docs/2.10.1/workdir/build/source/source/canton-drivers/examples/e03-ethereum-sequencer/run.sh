#!/usr/bin/env bash

# Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates
#
# Proprietary code. All rights reserved.

#######################################################################################################
# Starts a Canton domain with an Ethereum-backed sequencer using 4 Besu clients
# Usage is
# - `./run.sh simple` to run the demo with the simple scenario with only one sequencer
# - `./run.sh advanced` to run the demo with the advanced scenario with two sequencers
#
# Further CLI options (you will likely never need these):
# - `./run.sh <arg>` to use the docker compose file(s) <arg>
# - `./run.sh <arg> --data-dir <directory>` to write the Besu testnet data (mostly public/private key pairs) to
#   <directory> while using docker compose file(s) <arg>
#
# When using the demo with a non-default docker compose file, you may need to remove the previous data directory as root.
# You can set $ETHEREUM_DEMO_SUDO_RM to `true` to enable this.
#######################################################################################################

set -euo pipefail

function to-abs-path {
  local target="$1"

  if [ "$target" == "." ]; then
    # we use echo to return a value from the function
    # shellcheck disable=SC2005
    echo "$(pwd)"
  elif [ "$target" == ".." ]; then
    # we use echo to return a value from the function
    # shellcheck disable=SC2005
    echo "$(dirname "$(pwd)")"
  else
    echo "$(
      cd "$(dirname "$1")"
      pwd
    )/$(basename "$1")"
  fi
}

# get the full path to the script directory
ABSDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"

# Get the solidity output path
soliditydir="$(to-abs-path "/qbft-testnet")"
export SOLIDITY_OUTPUT=$soliditydir

export ETHEREUM_DEMO_DIR=$ABSDIR
export COMPOSE_PROJECT_NAME=canton-on-ethereum-demo
echo "COMPOSE_PROJECT_NAME is now $COMPOSE_PROJECT_NAME"
ETHEREUM_DEMO_SUDO_RM=${ETHEREUM_DEMO_SUDO_RM:-false}

# -- Begin of CLI parsing
DOCKER_COMPOSE_DIR="$ETHEREUM_DEMO_DIR/docker-compose"
if [[ $# -ge 1 ]] && [ "$1" == "simple" ]; then
  export COMPOSE_FILE="$DOCKER_COMPOSE_DIR/docker-compose-besu.yaml:$DOCKER_COMPOSE_DIR/docker-compose-simple.yaml"
  shift
elif [[ $# -ge 1 ]] && [ "$1" == "advanced" ]; then
  export COMPOSE_FILE="$DOCKER_COMPOSE_DIR/docker-compose-besu.yaml:$DOCKER_COMPOSE_DIR/docker-compose-advanced.yaml"
  shift
elif [[ $# -ge 1 ]]; then
  export COMPOSE_FILE=$1
  shift
else
  export COMPOSE_FILE="$DOCKER_COMPOSE_DIR/docker-compose-besu.yaml:$DOCKER_COMPOSE_DIR/docker-compose-simple.yaml"
fi

if [[ $# -ge 2 ]] && [ "$1" == "--data-dir" ]; then
  export DATA_DIR=$2
  shift
  shift
else
  export DATA_DIR="$ETHEREUM_DEMO_DIR"/qbft-testnet/testnet
fi
# -- End of CLI parsing

echo "Using compose file $COMPOSE_FILE"
# The data directory is the directory where the data of the Besu nodes will be saved
echo "Using data dir $DATA_DIR"

echo "shutting down any running nodes"
docker compose down
[[ -z $(docker ps --filter name=/besu-gen-testnet -aq) ]] || (docker stop besu-gen-testnet && docker rm /besu-gen-testnet)

echo "Removing previous testnet and generating a new clean testnet"
if [[ $ETHEREUM_DEMO_SUDO_RM == true ]]; then
  echo "Deleting $DATA_DIR as root..." && sudo rm -rf "$DATA_DIR"
else
  rm -rf "$DATA_DIR"
fi

# Generate genesis file, keys and certificates for a Besu testnet
docker run -i --name="besu-gen-testnet" \
  --entrypoint="/bin/bash" \
  --volume "$ETHEREUM_DEMO_DIR"/qbft-testnet:/opt/besu/gen:ro \
  hyperledger/besu:22.1.3 \
  -c "cd /opt/besu; cp -r gen/* .; ./generate-testnet.sh MANUAL_START"

ids="$(docker ps -a --filter "name=besu-gen-testnet" --format "{{.ID}}")"
id=$(echo "$ids" | head -n 1)
# Copy testnet to host directory
docker cp "$id":/opt/besu/testnet "$DATA_DIR"
chmod 777 -R "$DATA_DIR"
docker rm /besu-gen-testnet

echo "Shutting down any running nodes"
docker compose down

echo "Starting the Besu nodes and Canton"
docker compose up --force-recreate --remove-orphans --always-recreate-deps 2>&1 | tee log.txt
