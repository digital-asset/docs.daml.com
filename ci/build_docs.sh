#!/usr/bin/env bash

set -euo pipefail

DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

sdk_version=$(jq -r '.daml' $DIR/../LATEST)
canton_version=$(jq -r '.canton' $DIR/../LATEST)
target=$1
workdir=$(mktemp -d)
trap "rm -rf $workdir" EXIT
echo "Building documentation for sdk $sdk_version, canton $canton_version"
$DIR/../docs/download.sh $sdk_version $canton_version $workdir
$DIR/../docs/build.sh $sdk_version $canton_version $workdir $target
