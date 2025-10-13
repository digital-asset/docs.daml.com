#!/usr/bin/env bash

# Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates
#
# Proprietary code. All rights reserved.

#################################################################################################################
# Shuts down and removes all Docker containers started by `run.sh`
# Usage:
# - `stop-with-purge.sh`
#
# When using the demo with a different docker compose file you may need to remove the previous data directory as root.
# You can set $ETHEREUM_DEMO_SUDO_RM to `true` to enable this.
#################################################################################################################

set -eu -o pipefail
# get the full path to the script directory
ABSDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
cd "$ABSDIR" || exit

export ETHEREUM_DEMO_DIR=$ABSDIR
DOCKER_COMPOSE_DIR="$ETHEREUM_DEMO_DIR/docker-compose"
export COMPOSE_FILE="$DOCKER_COMPOSE_DIR/docker-compose-besu.yaml:$DOCKER_COMPOSE_DIR/docker-compose-simple.yaml:$DOCKER_COMPOSE_DIR/docker-compose-advanced.yaml"
export COMPOSE_PROJECT_NAME=canton-on-ethereum-demo
export DATA_DIR=${DATA_DIR:-"$ETHEREUM_DEMO_DIR/qbft-testnet/testnet"}
ETHEREUM_DEMO_SUDO_RM=${ETHEREUM_DEMO_SUDO_RM:-false}

docker compose down -v
[[ -z $(docker ps --filter name=/besu-gen-testnet -aq) ]] || docker rm /besu-gen-testnet
if [[ $ETHEREUM_DEMO_SUDO_RM == true ]]; then
  echo "Deleting $DATA_DIR as root..." && sudo rm -rf "$DATA_DIR"
else
  rm -rf "$DATA_DIR"
fi

cd -
