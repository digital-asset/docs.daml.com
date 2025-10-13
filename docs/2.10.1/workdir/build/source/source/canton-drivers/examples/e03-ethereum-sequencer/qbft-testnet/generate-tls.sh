#!/usr/bin/env bash

# Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates
#
# Proprietary code. All rights reserved.

###################################################################################
# Generate all the TLS certificates and files needed to start a Besu node and
#  Canton sequencer with TLS
# Usage is
# - `./generate-testnet SAN_BESU SAN_CANTON`
# where SAN stands for subject alternative name (used for hostname verification in TLS)
###################################################################################

SAN_BESU=$1 # e.g. SAN_BESU="DNS:localhost,DNS:besu-1,DNS:besu-2,IP:127.0.0.1"
SAN_CANTON=$2

mkdir -p tls
chmod 777 -R tls
cd tls || exit

# Generating self-signed certificates and putting them into key stores
openssl req -x509 -newkey rsa:4096 -keyout besu_key.pem -out besu_cert.pem -days 3650 -nodes -subj "/CN=besu-1/O=testing/OU=besu/emailAddress=canton@digitalasset.com" -addext "subjectAltName=$SAN_BESU"
openssl pkcs12 -export -out besu_store.p12 -inkey besu_key.pem -in besu_cert.pem -passout pass:password
openssl req -x509 -newkey rsa:4096 -keyout canton_key.pem -out canton_cert.pem -days 3650 -nodes -subj "/CN=canton/O=testing/OU=canton/emailAddress=canton@digitalasset.com" -addext "subjectAltName=$SAN_CANTON"
openssl pkcs12 -export -out canton_store.p12 -inkey canton_key.pem -in canton_cert.pem -passout pass:password

echo "password" >password.txt
fingerprint=$(keytool -list -v -keystore canton_store.p12 -storetype PKCS12 -storepass password | grep SHA256: | sed -e 's/SHA256: //')
echo "canton $fingerprint" >knownClients.txt

(
  cd ..
)
