add_library(VisionGrpc)

target_sources(
    VisionGrpc
    PUBLIC
        FILE_SET HEADERS
            TYPE HEADERS
            BASE_DIRS include
            FILES include/VisionGrpc/VisionService.h
    PRIVATE src/VisionService.cpp
)

enable_project_warnings(VisionGrpc)
target_compile_features(VisionGrpc PUBLIC cxx_std_26)
target_include_directories(VisionGrpc PUBLIC include)
target_link_libraries(VisionGrpc PUBLIC grpc::grpc)
