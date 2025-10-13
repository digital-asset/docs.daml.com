#!/usr/bin/env bash
# Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates
#
# Proprietary code. All rights reserved.

###################################################################################
# Starts a Besu node on the host. This function is expected to be called as part of `generate-testnet.sh` or
# `docker-compose-besu.yaml`
# Usage:
#   - `./start-node.sh <nodeName> <httpPort> <p2pPort> <bootnodeArgument> <extraBesuCliOptions>`
#
# Please refer to the code below for how <bootnodeArgument> is interpreted.
#
###################################################################################

set -euo pipefail

# turns off secp256k1 seed randomization. makes besu node startup faster but should NOT be used in a production setting
export BESU_OPTS="-Dsecp256k1.randomize=false" && echo "secp256k1 seed randomization is turned off. This should not be used in a production setting."
name=$1
httpPort=$2
p2pPort=$3

bootnodeArgument=$4
extraArgs=${5-}

if [ "$bootnodeArgument" == "in-container" ] && [ "$name" != "node1" ]; then
  # Get the IP address of the bootnode by looking for a host called besu-1 (this is the bootnode)
  bootnode_ip=$(getent hosts besu-1 | awk '{ print $1 }')
  ## Generate the flag used to point other nodes at the bootnode
  bootnode="--bootnodes=enode://2431593e92a1a9d0f9b8d0510137ddaa57cfbe14c78536f893471ba228654256bff529cc6d705fbf7aa60701250b2894f6741259e0a33d4879b74bf31b16fdc0@$bootnode_ip:30303"
  # Get the peer-to-peer ip address for this container
  p2pHost=$(awk 'END{print $1}' /etc/hosts)
elif [ "$bootnodeArgument" == "in-container" ] && [ "$name" == "node1" ]; then
  bootnode=""
  # Get the peer-to-peer ip address for this container
  p2pHost=$(awk 'END{print $1}' /etc/hosts)
else
  bootnode="$bootnodeArgument"
  p2pHost="0.0.0.0"
fi

# shellcheck disable=SC2086
besu --data-path="$name"/data \
  --genesis-file=genesis.json \
  --min-gas-price=0 \
  --rpc-http-enabled \
  --rpc-http-api=ETH,TXPOOL,WEB3,QBFT \
  --rpc-http-tls-enabled \
  --rpc-http-tls-keystore-file=tls/besu_store.p12 \
  --rpc-http-tls-keystore-password-file=tls/password.txt \
  --rpc-http-tls-client-auth-enabled \
  --rpc-http-tls-known-clients-file=tls/knownClients.txt \
  --host-allowlist="*" \
  --rpc-http-cors-origins="all" \
  --logging=INFO \
  --discovery-enabled=true \
  --p2p-port="$p2pPort" \
  --p2p-host="$p2pHost" \
  --rpc-http-port="$httpPort" $bootnode $extraArgs 2>&1 | tee -a /tmp/"$name".log
