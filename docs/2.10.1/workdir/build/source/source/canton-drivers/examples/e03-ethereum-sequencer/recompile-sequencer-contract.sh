#!/usr/bin/env bash

set -euo pipefail

# get the full path to the script directory
abs_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
canton_drivers="$abs_dir/../.."
sequencer_dir="$canton_drivers/drivers/ethereum/src/main"
contract_dir="$sequencer_dir/solidity"

artifacts="$abs_dir/qbft-testnet"
contract_name="Sequencer"
solc_version="0.8.10" # Should match the top line of Sequencer.sol

echo "shutting down any running nodes"
[[ -z $(docker ps --filter name=/solidity-compiler -aq) ]] || (docker stop solidity-compiler && docker rm /solidity-compiler)

echo "Compiling sequencer contract"

docker run \
  --name "solidity-compiler" \
  -v "$contract_dir":/sources \
  -v "$artifacts":/output \
  ethereum/solc:$solc_version \
  -o /output "/sources/$contract_name.sol" \
  --bin --abi --bin-runtime --optimize --optimize-runs=$((2 ** 32 - 1)) --overwrite

docker rm /solidity-compiler

echo "Generating Java bindings"
# web3j command line tool installed from here:
# http://docs.web3j.io/4.8.7/command_line_tools/#installation
web3j generate solidity --abiFile="$artifacts"/Sequencer.abi \
  --binFile="$artifacts"/Sequencer.bin \
  --outputDir="$sequencer_dir/java" \
  --package=com.digitalasset.canton.domain.sequencing.sequencer.ethereum
