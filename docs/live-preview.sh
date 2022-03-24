#!/usr/bin/env bash
# Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

set -eou pipefail


cd "$( dirname -- "${BASH_SOURCE[0]}" )"
BUILD_DIR=$PWD/build

RELEASE_TAG=$1
CANTON_RELEASE_TAG=$2
DOWNLOAD_DIR=$3


mkdir -p $BUILD_DIR/gen

./setup-sphinx-source-tree.sh $RELEASE_TAG $CANTON_RELEASE_TAG $DOWNLOAD_DIR $BUILD_DIR/source

DATE=$(date +"%Y-%m-%d")
echo { \"$DATE\" : \"$DATE\" } >  $BUILD_DIR/gen/versions.json

ln -s $PWD/index/index_html.rst $BUILD_DIR/source/source/index.rst

pipenv install
pipenv run sphinx-autobuild -c $BUILD_DIR/source/configs/html $BUILD_DIR/source/source $BUILD_DIR/gen
