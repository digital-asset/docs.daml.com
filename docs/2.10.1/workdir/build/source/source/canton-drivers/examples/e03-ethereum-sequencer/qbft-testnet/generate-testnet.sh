#!/usr/bin/env bash

# Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates
#
# Proprietary code. All rights reserved.

###################################################################################
# Generate a new Besu testnet (Keys, genesis file, TLS certificates for Canton and Besu)
# This script requires Besu to be installed locally (verify installation: `besu --version`) if it is called directly
# and not executed inside a Besu docker container (as when it's called by `run.sh`)
# Usage:
# - `./generate-testnet ` (automatically starts the Besu nodes on host)
# - `./generate-testnet AUTOMATIC_START` (automatically starts the Besu nodes on host)
# - `./generate-testnet MANUAL_START` (doesn't automatically start the Besu nodes on host)
# - `./generate-testnet MANUAL_START|AUTOMATIC_START <extraBesuCliArgs>`
# The argument `extraBesuCliArgs` is passed to the `start-node.sh` script when automatically starting the Besu nodes. It
# is ignored when the Besu nodes are configured to start manually.
###################################################################################

set -euo pipefail

# turns off secp256k1 seed randomization. makes besu node startup faster but should NOT be used in a production setting
export BESU_OPTS="-Dsecp256k1.randomize=false" && echo "secp256k1 seed randomization is turned off. This should not be used in a production setting."

# If the first variable $1 is set and equal to MANUAL_START, then don't start Besu nodes
if [[ $# -ge 1 && $1 == "MANUAL_START" ]]; then
  # This script can be run without starting Besu nodes, and it will generate keys and state for a new testnet.
  startNodes=false
  echo "Will generate testnet but not start Besu nodes."
elif [[ $# -ge 1 ]] && [ "$1" != "AUTOMATIC_START" ]; then
  echo "Unknown argument \$1: '$1'"
  exit 1
else
  startNodes=true
  echo "Will generate testnet and start Besu nodes."
fi
extraBesuCliArgs=${2-}

# Get the full path to the script directory
absdir="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
echo "$absdir"

# Remove the files from the previous testnet
rm -rf "$absdir/testnet" || true
mkdir -p "$absdir/testnet"
cp "$absdir/start-node.sh" "$absdir/testnet"
cp "$absdir/generate-tls.sh" "$absdir/testnet"
cp "$absdir/Sequencer.bin-runtime" "$absdir/testnet"

echo "Getting node addresses based on the node public keys"
nodes=(node1 node2 node3 node4)
addresses=()

cd "$absdir/testnet"
for i in "${nodes[@]}"; do
  # If there are some keys in `qbft-testnet/nodeX`, reuse them
  if [[ -d ""$absdir/$i/data"" ]]; then
    echo "Reusing keys for Besu node '$i'"
    cp -r "$absdir/$i" "$absdir/testnet/$i"
  else # Else generate new ones (default case)
    besu --data-path="$i"/data public-key export --to="$i"/data/key.pub
  fi

  # Get the address of the node, so that we can add the node as a validator
  address=$(besu --data-path="$i"/data public-key export-address | tail -n1)
  addresses+=("\"${address:2}\"")
done

# If the TLS directory exists, we assume it contains all required files and reuse them
if [[ -d ""$absdir/tls"" ]]; then
  echo "Reusing existing TLS certificates"
  cp -r "$absdir/tls" "$absdir/testnet/tls"
else # Else generate new ones (default case)
  echo "Generating new self-signed TLS certificates"
  ./generate-tls.sh "DNS:localhost,DNS:besu-1,DNS:besu-2,IP:127.0.0.1,IP:0.0.0.0" "DNS:localhost,DNS:enterprise-canton,IP:127.0.0.1,IP:0.0.0.0"
fi

# Write a file containing the addresses of the 4 nodes. These will be the initial validator nodes
cd "$absdir"
echo "[${addresses[0]},${addresses[1]},${addresses[2]},${addresses[3]}]" >testnet/toEncode.json

echo "Encoding validator nodes"
# Encode the initial validator nodes in the correct format for the genesis file
besu rlp encode --from=testnet/toEncode.json --to=testnet/encodedExtraData --type=QBFT_EXTRA_DATA

# Get the public key of node1. Node1 will be the bootnode. Use this public key to generate the bootnode url.
echo "Generating the bootnode url"
pubKey=$(<"$absdir/testnet/node1/data/key.pub")
bootnode="--bootnodes=enode://${pubKey:2}@127.0.0.1:30303"

# Regenerate the genesis file so that it uses the 4 new nodes as the initial validators
echo "Regenerating the genesis file (QBFT)"
extraData=$(cat testnet/encodedExtraData)
contractCode=$(cat testnet/Sequencer.bin-runtime)

echo '{
      "config": {
          "chainid": 1337,
          "berlinBlock": 0,
          "zeroBaseFee": true,
          "contractSizeLimit": 2147483647,
          "qbft": {
              "blockperiodseconds" : 1,
              "epochlength" : 30000,
              "requesttimeoutseconds" : 2
          }
      },
      "nonce": "0x0",
      "timestamp": "0x58ee40ba",
      "extraData": "'"$extraData"'",
      "gasLimit": "0x1fffffffffffff",
      "difficulty": "0x1",
      "mixHash": "0x63746963616c2062797a616e74696e65206661756c7420746f6c6572616e6365",
      "coinbase": "0x0000000000000000000000000000000000000000",
      "alloc": {
         "0x0af0238112db255e1a2c8a6c1cd4e122c56bbc38": {
               "code": "'"$contractCode"'",
               "storage": {
                "4": "0x312e302e3100000000000000000000000000000000000000000000000000000a"
               }
         }
      },
      "number": "0x0",
      "gasUsed": "0x0",
      "parentHash": "0x0000000000000000000000000000000000000000000000000000000000000000"
      }' >testnet/genesis.json

if [ "$startNodes" = true ]; then
  cd "$absdir/testnet"
  ./start-node.sh node1 8550 30303 "" "--graphql-http-enabled $extraBesuCliArgs" & # Enable graphql for inspecting the ledger / debugging
  ./start-node.sh node2 8551 30304 "$bootnode" "$extraBesuCliArgs" &
  ./start-node.sh node3 8552 30305 "$bootnode" "$extraBesuCliArgs" &
  ./start-node.sh node4 8553 30306 "$bootnode" "$extraBesuCliArgs"

fi
