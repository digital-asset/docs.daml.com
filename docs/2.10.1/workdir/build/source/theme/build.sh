#!/usr/bin/env bash

set -euo pipefail

DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

cd $DIR

npm install

npm exec grunt build

sass -I bower_components_static/bourbon/dist \
     -I bower_components_static/neat/app/assets/stylesheets \
     -I bower_components_static/font-awesome/scss \
     -I bower_components_static/wyrm/sass \
     --style compressed \
     --sourcemap=none \
     --update \
     sass:da_theme/static/css