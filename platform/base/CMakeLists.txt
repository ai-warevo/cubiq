cmake_minimum_required(VERSION 3.15)
project(cubiq_platform_base)

add_library(platform_base INTERFACE)

target_include_directories(platform_base INTERFACE ${CMAKE_SOURCE_DIR})
