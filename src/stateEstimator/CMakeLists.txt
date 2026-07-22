add_library(StateEstimator)

target_sources(
    StateEstimator
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS include
            TYPE HEADERS
            FILES include/StateEstimator/KalmanFilter.h
    PRIVATE src/KalmanFilter.cpp
)

target_compile_features(StateEstimator PUBLIC cxx_std_26)
target_include_directories(StateEstimator PUBLIC include)
target_link_libraries(StateEstimator PUBLIC Eigen3::Eigen Models DataStreamer)
