add_subdirectory(config)
add_subdirectory(cheats)
add_subdirectory(gui)
add_subdirectory(math)
add_subdirectory(modes)
add_subdirectory(structures)

add_library(cubiq_common INTERFACE)
target_link_libraries(cubiq_common INTERFACE 
    platform_base
    cubiq_config
    cubiq_cheats
    cubiq_gui
    cubiq_math
    cubiq_structures
)
