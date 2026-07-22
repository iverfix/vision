cmake_minimum_required(VERSION 4.3.4)
project(Vision)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/app)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/data_streamer)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/feature_matcher)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/camera)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/state_estimator)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/models)

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    execute_process(
        COMMAND
            ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_SOURCE_DIR}/compile_commands.json
    )
endif()
