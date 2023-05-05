#!/usr/bin/env bash

set -eou pipefail

DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

RELEASE_TAG=$1
CANTON_RELEASE_TAG=$2
SOURCE_DIR=$3
TARGET_DIR=$4

echo "Building docs for $RELEASE_TAG"

BUILD_DIR=$SOURCE_DIR/build

mkdir -p $BUILD_DIR/sphinx-source $BUILD_DIR/sphinx-target

$DIR/setup-sphinx-source-tree.sh $RELEASE_TAG $CANTON_RELEASE_TAG $SOURCE_DIR $BUILD_DIR/sphinx-source

declare -A sphinx_targets=( [html]=html [pdf]=latex )
declare -A sphinx_flags=( [html]=-W [pdf]=-W )

for name in "${!sphinx_targets[@]}"; do
    target=${sphinx_targets[$name]}
    cp $DIR/index/index_$name.rst $BUILD_DIR/sphinx-source/source/index.rst
    sphinx-build ${sphinx_flags[$name]} --color -b $target -c $BUILD_DIR/sphinx-source/configs/$name $BUILD_DIR/sphinx-source/source $BUILD_DIR/sphinx-target/$name
done

# Build PDF docs
tar xf $SOURCE_DIR/pdf-fonts-$RELEASE_TAG.tar.gz -C $BUILD_DIR/sphinx-target/pdf
cd $BUILD_DIR/sphinx-target/pdf
lualatex -halt-on-error -interaction=batchmode --shell-escape *.tex
lualatex -halt-on-error -interaction=batchmode --shell-escape *.tex
cd -
mv $BUILD_DIR/sphinx-target/pdf/DigitalAssetSDK.pdf $TARGET_DIR/pdf-docs-$RELEASE_TAG.pdf

# Merge HTML docs
tar xf $SOURCE_DIR/non-sphinx-html-docs-$RELEASE_TAG.tar.gz -C $BUILD_DIR/sphinx-target/html --strip-components=1
DATE=$(date --rfc-3339=date)
cp $TARGET_DIR/pdf-docs-$RELEASE_TAG.pdf $BUILD_DIR/sphinx-target/html/_downloads/DigitalAssetSDK.pdf
mkdir $BUILD_DIR/sphinx-target/html/canton/scaladoc
tar xf $SOURCE_DIR/canton-scaladoc-$CANTON_RELEASE_TAG.tar.gz  -C $BUILD_DIR/sphinx-target/html/canton/scaladoc  --strip-components=1
rm -r $BUILD_DIR/sphinx-target/html/.buildinfo $BUILD_DIR/sphinx-target/html/.doctrees $BUILD_DIR/sphinx-target/html/objects.inv
(
    cd $BUILD_DIR/sphinx-target/html
    SMHEAD="<?xml version='1.0' encoding='UTF-8'?><urlset xmlns='http://www.sitemaps.org/schemas/sitemap/0.9' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:schemaLocation='http://www.sitemaps.org/schemas/sitemap/0.9 http://www.sitemaps.org/schemas/sitemap/0.9/sitemap.xsd'>"
    SMITEM="<url><loc>%LOC%</loc><lastmod>${DATE}</lastmod><changefreq>daily</changefreq><priority>0.8</priority></url>"
    SMFOOT="</urlset>"
    echo $SMHEAD > sitemap.xml
    while read item; do
        echo $SMITEM | sed -e "s,%LOC%,${item}," >> sitemap.xml
    done < <(find . -name '*.html' | sort | sed -e 's,^\./,https://docs.daml.com/,')
    echo $SMFOOT >> sitemap.xml
)
tar cfz $TARGET_DIR/html-docs-$RELEASE_TAG.tar.gz  -C $BUILD_DIR/sphinx-target html
