#!/usr/bin/env bash
# Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

set -eou pipefail

DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

cd "$DIR"

RELEASE_TAG=$(jq -r '.daml' ../LATEST)
CANTON_RELEASE_TAG=$(jq -r '.canton' ../LATEST)
DAML_FINANCE_RELEASE_TAG=$(jq -r '.daml_finance' ../LATEST)
DOWNLOAD_DIR=workdir/downloads
SPHINX_DIR=workdir/build/source

prefix=$(jq -r '.prefix' ../LATEST)

mkdir -p $SPHINX_DIR/source/canton $SPHINX_DIR/source/daml-finance
tar xf $DOWNLOAD_DIR/sphinx-source-tree-$RELEASE_TAG.tar.gz -C $SPHINX_DIR --strip-components=1
tar xf $DOWNLOAD_DIR/canton-docs-$CANTON_RELEASE_TAG.tar.gz -C $SPHINX_DIR/source/canton

cp $SPHINX_DIR/source/canton/exts/canton_enterprise_only.py $SPHINX_DIR/configs/static/

# Rewrite Canton's absolute references.
find $SPHINX_DIR/source/canton -type f -print0 | while IFS= read -r -d '' file
do
    sed -i 's|include:: /substitution.hrst|include:: /canton/substitution.hrst|g ; s|image:: /images|image:: /canton/images|g' $file
    sed -i "s|__VERSION__|$prefix|g" $file
done

# Drop Canton’s index in favor of our own.
rm $SPHINX_DIR/source/canton/index.rst

declare -A sphinx_targets=( [html]=html [pdf]=latex )

sed -i "s/'sphinx.ext.extlinks',$/'sphinx.ext.extlinks','canton_enterprise_only','sphinx.ext.todo',/g" $SPHINX_DIR/configs/html/conf.py
sed -i "s/'sphinx.ext.extlinks'$/'sphinx.ext.extlinks','canton_enterprise_only','sphinx.ext.todo'/g" $SPHINX_DIR/configs/pdf/conf.py

# We rename the PDF so need to update the link.
sed -i "s/DigitalAssetSDK\\.pdf/DamlEnterprise$prefix.pdf/" $SPHINX_DIR/theme/da_theme/layout.html

# Setting version number
for file in pdf html; do
    for var in version release; do
        sed -i "s|$var = u'.*'|$var = u'$prefix'|" $SPHINX_DIR/configs/$file/conf.py
    done
done

cp -r index $SPHINX_DIR/source/index
mv -f $SPHINX_DIR/source/index/index.rst $SPHINX_DIR/source/index.rst

# Title page on the PDF
sed -i "s|Version : .*|Version : $prefix|" $SPHINX_DIR/configs/pdf/conf.py
