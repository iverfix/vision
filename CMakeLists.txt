cmake_minimum_required(VERSION 4.3.4)
project(Vision)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Vision)
target_compile_features(Vision PRIVATE cxx_std_26)

target_sources(Vision PUBLIC src/main.cpp)
