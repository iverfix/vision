add_library(DataStreamer)
add_library(Vision::DataStreamer ALIAS DataStreamer)

target_sources(
    DataStreamer
    PUBLIC
        FILE_SET HEADERS
            TYPE HEADERS
            BASE_DIRS include
            FILES
                include/DataStreamer/ImageStreamer.h
                include/DataStreamer/DataTypes.h
                include/DataStreamer/OxtsStreamer.h
    PRIVATE
        src/StreamerUtil.h
        src/StreamerUtil.cpp
        src/ImageStreamer.cpp
        src/OxtsStreamer.cpp
)

enable_project_warnings(DataStreamer)
target_compile_features(DataStreamer PUBLIC cxx_std_26)
target_include_directories(DataStreamer PUBLIC include)
target_link_libraries(DataStreamer PUBLIC opencv::opencv)
