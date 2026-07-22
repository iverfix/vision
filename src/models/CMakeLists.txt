add_library(Models)

target_sources(
    Models
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS include
            TYPE HEADERS
            FILES include/Models/ConstantVelocity.h
    PRIVATE src/ConstantVelocity.cpp
)

target_compile_features(Models PUBLIC cxx_std_26)
target_include_directories(Models PUBLIC include)
target_link_libraries(Models Eigen3::Eigen)
