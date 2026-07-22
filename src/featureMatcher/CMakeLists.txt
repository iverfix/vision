add_library(FeatureMatcher)

target_sources(
    FeatureMatcher
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS include
            TYPE HEADERS
            FILES include/FeatureMatcher/featureMatcher.h
    PRIVATE src/featureMatcher.cpp
)

target_include_directories(FeatureMatcher PUBLIC include)
target_compile_features(FeatureMatcher PUBLIC cxx_std_26)
target_link_libraries(FeatureMatcher PUBLIC opencv::opencv Camera)
