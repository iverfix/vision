add_executable(Vision src/vision.cpp)

target_compile_features(Vision PUBLIC cxx_std_26)
enable_project_warnings(Vision)

target_compile_definitions(
    Vision
    PRIVATE PROJECT_ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(
    Vision
    PRIVATE
        opencv::opencv
        Eigen3::Eigen
        DataStreamer
        FeatureMatcher
        Camera
        StateEstimator
)
