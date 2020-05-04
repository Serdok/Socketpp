cmake_minimum_required(VERSION 3.13)
project(Socketpp)

set(CMAKE_CXX_STANDARD 20)

add_library(Socketpp SHARED)
add_subdirectory(src)

set_target_properties(Socketpp PROPERTIES
        VERSION 1.0.0
        SOVERSION 1
        PUBLIC_HEADER include/Socketpp.h)
target_include_directories(Socketpp PUBLIC include)