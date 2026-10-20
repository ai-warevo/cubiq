cmake_minimum_required(VERSION 3.15)
project(cubiq_kernel_client)

add_library(cubiq_kernel_client INTERFACE)
target_compile_definitions(cubiq_kernel_client INTERFACE CUBIQ_PLATFORM="x86")

# Add client sources here...
# add_executable(cubiq_kernel_client 
#     src/main.cpp
# )
