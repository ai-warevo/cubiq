cmake_minimum_required(VERSION 3.10)
project(cubiq_onehitkill)

add_library(cubiq_onehitkill STATIC
    src/OneHitKillConfig.cpp
)

target_include_directories(cubiq_onehitkill PUBLIC inc ${CMAKE_SOURCE_DIR})
target_link_libraries(cubiq_onehitkill PUBLIC cubiq_config)
