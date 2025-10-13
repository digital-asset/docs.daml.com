FROM hyperledger/fabric-tools:2.5.4

COPY ./ /opt/ledger-setup/

WORKDIR /opt/ledger-setup/

RUN ./network.sh createCrypto
