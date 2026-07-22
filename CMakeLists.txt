cmake_minimum_required(VERSION 4.3.4)
project(Vision)

set(PROJECT_ROOT_DIR "${CMAKE_SOURCE_DIR}" CACHE PATH "Project root directory")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CreateCompileCommandsSymlink)
include(Dependencies)
include(CompilerWarnings)

add_subdirectory(src/app)
add_subdirectory(src/data_streamer)
add_subdirectory(src/feature_matcher)
add_subdirectory(src/camera)
add_subdirectory(src/state_estimator)
add_subdirectory(src/models)
add_subdirectory(src/vision_grpc)

create_compile_commands_symlink()
