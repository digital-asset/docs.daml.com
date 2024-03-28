#!/usr/bin/env bash
# Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

set -eou pipefail


DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

cd "$DIR"

BUILD_DIR=workdir/build
rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR

RELEASE_TAG=$(jq -r '.daml' ../LATEST)
CANTON_RELEASE_TAG=$(jq -r '.canton' ../LATEST)
DOWNLOAD_DIR=workdir/downloads


mkdir -p $BUILD_DIR/gen

./setup-sphinx-source-tree.sh

DATE=$(date +"%Y-%m-%d")
echo { \"$DATE\" : \"$DATE\" } >  $BUILD_DIR/gen/versions.json

ln -s $PWD/index/index_html.rst $BUILD_DIR/source/source/index.rst

pipenv install
pipenv run sphinx-autobuild -c $BUILD_DIR/source/configs/html $BUILD_DIR/source/source $BUILD_DIR/gen
