#!/usr/bin/env bash
# Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

set -eou pipefail

DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

cd "$DIR"

RELEASE_TAG=$(jq -r '.daml' ../LATEST)
CANTON_RELEASE_TAG=$(jq -r '.canton' ../LATEST)
DAML_FINANCE_RELEASE_TAG=$(jq -r '.daml_finance' ../LATEST)
TARGET_DIR=../workdir/downloads

mkdir -p "$TARGET_DIR"

if [ -z "${ARTIFACTORY_USERNAME:-}" ] || [ -z "${ARTIFACTORY_PASSWORD:-}" ]; then
    echo "You need to set the ARTIFACTORY_USERNAME and ARTIFACTORY_PASSWORD env vars."
    echo "You can use .envrc.private for that; see README.md."
    exit 1
fi

echo "Downloading docs for $RELEASE_TAG"

source_tree=sphinx-source-tree-$RELEASE_TAG.tar.gz
non_sphinx_docs=non-sphinx-html-docs-$RELEASE_TAG.tar.gz
pdf_fonts=pdf-fonts-$RELEASE_TAG.tar.gz
for FILE in $source_tree $non_sphinx_docs $pdf_fonts; do
    curl -u $ARTIFACTORY_USERNAME:$ARTIFACTORY_PASSWORD \
         --fail \
         --location \
         https://digitalasset.jfrog.io/artifactory/assembly/daml/$RELEASE_TAG/docs/$FILE \
         > "$TARGET_DIR/$FILE"
done
curl -u $ARTIFACTORY_USERNAME:$ARTIFACTORY_PASSWORD \
    --fail \
    --location \
    https://digitalasset.jfrog.io/artifactory/assembly/canton/$CANTON_RELEASE_TAG/canton-doc-sources-$CANTON_RELEASE_TAG.tar.gz \
    > "$TARGET_DIR/canton-docs-$CANTON_RELEASE_TAG.tar.gz"
curl -u $ARTIFACTORY_USERNAME:$ARTIFACTORY_PASSWORD \
    --fail \
    --location \
    https://digitalasset.jfrog.io/artifactory/assembly/canton/$CANTON_RELEASE_TAG/canton-scaladoc-$CANTON_RELEASE_TAG.tar.gz \
    > "$TARGET_DIR/canton-scaladoc-$CANTON_RELEASE_TAG.tar.gz"
curl -u $ARTIFACTORY_USERNAME:$ARTIFACTORY_PASSWORD \
    --fail \
    --location \
    https://digitalasset.jfrog.io/artifactory/assembly/daml-finance/$DAML_FINANCE_RELEASE_TAG/daml-finance-doc-sources-$DAML_FINANCE_RELEASE_TAG.tar.gz \
    > "$TARGET_DIR/daml-finance-docs-$DAML_FINANCE_RELEASE_TAG.tar.gz"
