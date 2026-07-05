cmake_minimum_required(VERSION 4.3.4)
project(Vision)

find_package(OpenCV)
find_package(Eigen3)

add_executable(Vision)
target_compile_features(Vision PRIVATE cxx_std_26)

target_sources(Vision PUBLIC src/main.cpp)

target_link_libraries(Vision PRIVATE opencv::opencv Eigen3::Eigen)

