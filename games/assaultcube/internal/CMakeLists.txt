cmake_minimum_required(VERSION 3.15)
project(cubiq_internal)

add_library(cubiq_internal INTERFACE)
target_compile_definitions(cubiq_internal INTERFACE CUBIQ_PLATFORM="x86")

add_subdirectory(aimbot)
add_subdirectory(esp)
add_subdirectory(godmode)
