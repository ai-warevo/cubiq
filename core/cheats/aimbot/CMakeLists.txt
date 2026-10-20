cmake_minimum_required(VERSION 3.15)
project(cubiq_aimbot)

add_library(cubiq_aimbot INTERFACE)
target_include_directories(cubiq_aimbot INTERFACE inc ${CMAKE_SOURCE_DIR})
