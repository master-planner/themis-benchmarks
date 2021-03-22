#!/usr/bin/env bash
set -eo pipefail

rm -Rf src/proto/*

./third-party/protobuf/src/protoc --cpp_out=src/proto \
  --proto_path=resources/proto \
  test.proto