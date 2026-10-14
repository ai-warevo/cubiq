cmake_minimum_required(VERSION 3.15)
project(cubiq)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Logic for selective building via -D flags from Makefile
if(COMMON_ONLY)
    add_subdirectory(app/common)
    return()
endif()

if(INTERNAL_ONLY)
    # We need common to build internal, so we must include it
    add_subdirectory(app/common)
    add_subdirectory(app/internal)
    return()
endif()

if(EXTERNAL_ONLY)
    add_subdirectory(app/common)
    add_subdirectory(app/external)
    return()
endif()

if(KERNEL_ONLY)
    add_subdirectory(app/common)
    add_subdirectory(app/kernel)
    return()
endif()

# Default: build everything
add_subdirectory(app)
