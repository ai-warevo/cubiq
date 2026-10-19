cmake_minimum_required(VERSION 3.10)
project(cubiq_esp)

add_library(cubiq_esp INTERFACE)
target_include_directories(cubiq_esp INTERFACE inc ${CMAKE_SOURCE_DIR})
