cmake_minimum_required(VERSION 3.10)
project(cubiq_utils)

add_library(cubiq_utils INTERFACE)
target_include_directories(cubiq_utils INTERFACE inc ${CMAKE_SOURCE_DIR})
