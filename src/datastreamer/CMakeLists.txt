add_library(DataStreamer)

target_sources(
    DataStreamer
    PUBLIC FILE_SET HEADERS FILES ImageStreamer.h DataTypes.h
    PRIVATE StreamerUtil.h StreamerUtil.cpp ImageStreamer.cpp
)

target_compile_features(DataStreamer PRIVATE cxx_std_26)

target_link_libraries(DataStreamer PUBLIC opencv::opencv)
