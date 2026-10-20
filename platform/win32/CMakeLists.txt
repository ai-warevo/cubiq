cmake_minimum_required(VERSION 3.15)
project(cubiq_platform_win32)

add_library(platform_win32 STATIC
    src/Win32Input.cpp
    src/Win32Process.cpp
    src/Win32ProcessManager.cpp
    src/Win32WindowManager.cpp
)

target_include_directories(platform_win32 PUBLIC inc)
target_link_libraries(platform_win32 PUBLIC platform_base)
