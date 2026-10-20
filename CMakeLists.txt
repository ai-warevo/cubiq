cmake_minimum_required(VERSION 3.15)
project(cubiq)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(platform)
add_subdirectory(core)

if(NOT COMMON_ONLY)
    add_subdirectory(games)
endif()
