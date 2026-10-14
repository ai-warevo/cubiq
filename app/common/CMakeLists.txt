add_subdirectory(config)
add_subdirectory(cheats)
add_subdirectory(gui)
add_subdirectory(math)
add_subdirectory(structures)
add_subdirectory(utils)

add_library(cubiq_common INTERFACE)
target_link_libraries(cubiq_common INTERFACE 
    cubiq_config
    cubiq_cheats
    cubiq_gui
    cubiq_math
    cubiq_structures
    cubiq_utils
)
