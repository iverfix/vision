add_library(Camera)

target_sources(
    Camera
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS include
            TYPE HEADERS
            FILES include/Camera/Camera.h
    PRIVATE src/Camera.cpp
)

target_include_directories(Camera PUBLIC include)

target_link_libraries(Camera PUBLIC Eigen3::Eigen)
