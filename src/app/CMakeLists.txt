add_executable(Vision src/vision.cpp)

target_compile_features(Vision PUBLIC cxx_std_26)
enable_project_warnings(Vision)

target_compile_definitions(
    Vision
    PRIVATE PROJECT_ROOT_DIR="${PROJECT_ROOT_DIR}"
)

target_link_libraries(
    Vision
    PRIVATE
        opencv::opencv
        Eigen3::Eigen
        Vision::DataStreamer
        Vision::FeatureMatcher
        Vision::Camera
        Vision::StateEstimator
)
