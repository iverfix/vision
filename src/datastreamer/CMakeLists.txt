add_library(DataStreamer)

target_sources(
    DataStreamer
    PUBLIC FILE_SET HEADERS FILES DataStreamer.h
    PRIVATE DataStreamer.cpp
)

target_compile_features(DataStreamer PRIVATE cxx_std_26)

target_link_libraries(DataStreamer PUBLIC opencv::opencv)
