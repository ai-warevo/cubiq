cmake_minimum_required(VERSION 3.15)
project(cubiq_config)

add_library(cubiq_config STATIC
    src/BaseConfig.cpp
)

target_include_directories(cubiq_config PUBLIC inc ${CMAKE_SOURCE_DIR})
