# Canton-on-Ethereum Integration

The Canton-on-Ethereum integration runs a Canton domain where events are sequenced by an Ethereum-backed sequencer.

The folder `ethereum-docker-compose` contains pre-packaged docker-compose files to run Canton with an Ethereum domain,
as well as supporting scripts and the documentation.
The folder `qbft-testnet` contains scripts to generate and start an QBFT-protocol based testnet of Besu nodes.

Check [Ethereum Domain](https://docs.daml.com/canton/usermanual/domains/ethereum.html) for instructions for this demo and
broader Ethereum Sequencer usage. The scripts also always start with a short description of what they are doing.
