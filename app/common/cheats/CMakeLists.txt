add_subdirectory(aimbot)
add_subdirectory(esp)
add_subdirectory(godmode)
add_subdirectory(onehitkill)

add_library(cubiq_cheats INTERFACE)
target_include_directories(cubiq_cheats INTERFACE inc ${CMAKE_SOURCE_DIR})
target_link_libraries(cubiq_cheats INTERFACE 
    cubiq_aimbot 
    cubiq_esp 
    cubiq_godmode 
    cubiq_onehitkill
)
