add_library(FeatureMatcher)

target_sources(
    FeatureMatcher
    PUBLIC
    FILE_SET HEADERS
    FILES
    featureMatcher.h
    PRIVATE
    featureMatcher.cpp
)

target_link_libraries(
    FeatureMatcher
    PUBLIC
    opencv::opencv
)
