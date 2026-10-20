cmake_minimum_required(VERSION 3.15)
project(cubiq_platform_win32)

add_library(platform_win32 STATIC
    Win32Input.cpp
    Win32Process.cpp
    Win32ProcessManager.cpp
    Win32WindowManager.cpp
)

target_include_directories(platform_win32 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_SOURCE_DIR})
target_link_libraries(platform_win32 PUBLIC platform_base)
