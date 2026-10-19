cmake_minimum_required(VERSION 3.10)
project(cubiq_utils)

add_library(cubiq_utils STATIC 
    src/ProcessUtils.cpp
    src/InputUtils.cpp
    src/WindowUtils.cpp
    src/Process.cpp
)

target_include_directories(cubiq_utils PUBLIC inc ${CMAKE_SOURCE_DIR})
