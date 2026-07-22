cmake_minimum_required(VERSION 4.3.4)
project(Vision)

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

create_compile_commands_symlink()
