find_package(Protobuf REQUIRED)
set(PROTO_ROOT ${PROJECT_SOURCE_DIR}/proto)

message(STATUS "Protobuf version: ${Protobuf_VERSION}")
message(STATUS "protoc: ${Protobuf_PROTOC_EXECUTABLE}")

protobuf_generate_cpp(
    PROTO_SRCS
    PROTO_HDRS
    ${PROTO_ROOT}/vision/v1/measurement.proto
)

add_library(vision_proto ${PROTO_SRCS} ${PROTO_HDRS})

target_include_directories(vision_proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(vision_proto PUBLIC protobuf::libprotobuf)
