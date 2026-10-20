cmake_minimum_required(VERSION 3.15)
project(cubiq_internal)

set(CUBIQ_PLATFORM x86)
add_compile_definitions(CUBIQ_PLATFORM="${CUBIQ_PLATFORM}")

add_subdirectory(aimbot)
add_subdirectory(esp)
add_subdirectory(godmode)
add_subdirectory(src)
