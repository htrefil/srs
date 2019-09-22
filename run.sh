#!/usr/bin/env sh

set -e
make -j16
./bin/srs config.toml