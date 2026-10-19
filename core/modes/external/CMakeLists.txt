cmake_minimum_required(VERSION 3.15)
project(cubiq_core_modes_external)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "inc/*.hpp")

add_library(cubiq_core_modes_external STATIC ${SOURCES} ${HEADERS})

target_include_directories(cubiq_core_modes_external PUBLIC inc ${CMAKE_SOURCE_DIR})
target_link_libraries(cubiq_core_modes_external PRIVATE cubiq_common)
