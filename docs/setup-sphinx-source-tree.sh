#!/usr/bin/env bash

set -eou pipefail

DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

RELEASE_TAG=$1
CANTON_RELEASE_TAG=$2
DOWNLOAD_DIR=$3
SPHINX_DIR=$4

prefix=$(jq -r '.prefix' $DIR/../LATEST)

mkdir -p $SPHINX_DIR/source/canton
tar xf $DOWNLOAD_DIR/sphinx-source-tree-$RELEASE_TAG.tar.gz -C $SPHINX_DIR --strip-components=1
tar xf $DOWNLOAD_DIR/canton-docs-$CANTON_RELEASE_TAG.tar.gz -C $SPHINX_DIR/source/canton

cp $SPHINX_DIR/source/canton/exts/canton_enterprise_only.py $SPHINX_DIR/configs/static/

# Rewrite absolute references.
find $SPHINX_DIR/source/canton -type f -print0 | while IFS= read -r -d '' file
do
    sed -i 's|include:: /substitution.hrst|include:: /canton/substitution.hrst|g ; s|image:: /images|image:: /canton/images|g' $file
    sed -i "s|__VERSION__|$prefix|g" $file
done
sed -i '/^  concepts$/d' $SPHINX_DIR/source/canton/tutorials/tutorials.rst

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
