cmake_minimum_required(VERSION 3.10)
project(cubiq_godmode)

add_library(cubiq_godmode STATIC
    src/GodModeConfig.cpp
)

target_include_directories(cubiq_godmode PUBLIC inc ${CMAKE_SOURCE_DIR})
target_link_libraries(cubiq_godmode PUBLIC cubiq_config)
