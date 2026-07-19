add_library(StateEstimator)

target_sources(
    StateEstimator
    PUBLIC FILE_SET HEADERS FILES KalmanFilter.h
    PRIVATE KalmanFilter.cpp
)

target_compile_features(StateEstimator PRIVATE cxx_std_26)
target_link_libraries(StateEstimator PUBLIC Eigen3::Eigen Models)
