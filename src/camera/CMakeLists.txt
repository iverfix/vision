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
enable_project_warnings(Camera)
target_include_directories(Camera PUBLIC include)
target_compile_features(Camera PUBLIC cxx_std_26)
target_link_libraries(Camera PUBLIC Eigen3::Eigen)
