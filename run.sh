#!/usr/bin/env sh

set -e
make -j16
./srs config.toml