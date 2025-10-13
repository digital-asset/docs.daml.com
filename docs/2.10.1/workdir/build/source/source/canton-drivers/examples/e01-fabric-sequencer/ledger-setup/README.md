# Ledger setup

These files are based on the `fabric-samples`'s `test-network` (https://github.com/hyperledger/fabric-samples/tree/v2.0.0/test-network), which is explained at https://hyperledger-fabric.readthedocs.io/en/latest/test_network.html.

Here is a simplified, customized version of it that runs in a docker container based on the `hyperledger/fabric-tools` image as part of a docker-compose setup and spins up a Fabric ledger running Canton's Fabric Sequencer chaincode.

## macOS support

When using Docker Desktop on macOS, switch file sharing from gRPC FUSE to VirtioFS (available in macOS 12.5 and above).
