cmake_minimum_required(VERSION 3.15)
project(cubiq_math)

add_library(cubiq_math INTERFACE)
target_include_directories(cubiq_math INTERFACE inc ${CMAKE_SOURCE_DIR})
