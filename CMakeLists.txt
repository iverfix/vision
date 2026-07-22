cmake_minimum_required(VERSION 4.3.4)
project(Vision)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CreateCompileCommandsSymlink)
include(Dependencies)
include(CompilerWarnings)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/app)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/data_streamer)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/feature_matcher)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/camera)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/state_estimator)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/models)

create_compile_commands_symlink()
