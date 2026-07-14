add_library(Models)

target_sources(
    Models
    PUBLIC FILE_SET HEADERS FILES ConstantVelocity.h
    PRIVATE ConstantVelocity.cpp
)

target_compile_features(Models PRIVATE cxx_std_26)

target_link_libraries(Models Eigen3::Eigen)
