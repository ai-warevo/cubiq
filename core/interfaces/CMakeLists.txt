cmake_minimum_required(VERSION 3.15)
project(cubiq_interfaces)

add_library(cubiq_interfaces INTERFACE)
target_include_directories(cubiq_interfaces INTERFACE inc ${CMAKE_SOURCE_DIR})
