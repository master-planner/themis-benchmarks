cmake_minimum_required(VERSION 3.16)
project(experiment)

set(CMAKE_CXX_STANDARD 20)
find_package(protobuf CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)

include_directories(src src/proto ${RAPIDJSON_INCLUDE_DIRS})

add_executable(experiment main.cpp src/proto/test.pb.cc)
target_link_libraries(experiment PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
