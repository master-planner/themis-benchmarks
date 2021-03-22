In this document we analyse two widely adopted data formats in order to understand the storage requirements for each of them:

* JSON
* Protobuf

# Scenarios used for tests

## JSON with one letter key

```json
{"a": "works as a charm"}
```

The equivalent schema for Protobuf is:

```proto
message Test {
    string a = 1;
}
```

## List of JSON objects with one letter key

{"a": [
    {"a": "works as a charm"},
    {"a": "works as a charm"},
    {"a": "works as a charm"},
    {"a": "works as a charm"},
    {"a": "works as a charm"},
    {"a": "works as a charm"},
    {"a": "works as a charm"},
    {"a": "works as a charm"}
]}

The equivalent protobuf schems is:

```proto
message Test {
    string a = 1;
}

message TestList {
    repeated Test data = 1;
}

message TestWrapper {
    TestList a = 1;
}
```

# Results

|**Experiment**|**JSON** (bytes) |**Proto** (bytes) | **JSON Overhead** |
|--------------|-----------------|------------------|-------------------|
|**Single object**| 24 | 18 | 33% |
|**Complex array**| 207 | 163 | 27% |

## Local setup

The setup steps are tested on Ubuntu 20.04 version.

```bash
pushd third-party/protobuf
./autogen.sh
./configure
make -j32
popd

./scripts/compile-proto.sh
```