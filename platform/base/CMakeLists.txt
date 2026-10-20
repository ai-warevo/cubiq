cmake_minimum_required(VERSION 3.15)
project(cubiq_platform_base)

add_library(platform_base INTERFACE)

target_include_directories(platform_base INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)
