cmake_minimum_required(VERSION 3.10)
project(cubiq_structures)

add_library(cubiq_structures INTERFACE)
target_include_directories(cubiq_structures INTERFACE inc ${CMAKE_SOURCE_DIR})
