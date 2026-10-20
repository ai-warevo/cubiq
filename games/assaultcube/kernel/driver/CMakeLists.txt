cmake_minimum_required(VERSION 3.15)
project(cubiq_kernel_driver)

add_library(cubiq_kernel_driver INTERFACE)
target_compile_definitions(cubiq_kernel_driver INTERFACE CUBIQ_PLATFORM="x64")

# Add driver sources here...
