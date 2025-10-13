#!/usr/bin/env sh
# Wait for one or more ports to be open

set -euo

waitPortOpen() {
  echo "    waiting for port $1"
  while ! nc -z localhost "$1"; do sleep 1; done
  echo "    done waiting for port $1"
}

for port in "$@"; do
  waitPortOpen "$port" &
done

wait
