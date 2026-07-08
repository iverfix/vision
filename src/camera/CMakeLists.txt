add_library(Camera)

target_sources(Camera
    PUBLIC
    FILE_SET HEADERS
    FILES
    Camera.h
    PRIVATE
    Camera.cpp)

target_link_libraries(Camera PUBLIC Eigen3::Eigen)
