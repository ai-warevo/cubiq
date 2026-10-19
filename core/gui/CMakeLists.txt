cmake_minimum_required(VERSION 3.10)
project(cubiq_gui)

add_library(cubiq_gui INTERFACE)
target_include_directories(cubiq_gui INTERFACE inc ${CMAKE_SOURCE_DIR})
