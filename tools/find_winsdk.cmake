function(FIND_WINSDK_ITEM ARG_NAME ITEM_NAME TYPE)
    if(NOT DEFINED CUBIQ_PLATFORM)
        set(CUBIQ_PLATFORM x86)
    endif()

    # Determine search subdirectory based on type
    if(TYPE STREQUAL "PROGRAM")
        set(SEARCH_SUBDIR "bin")
    else()
        set(SEARCH_SUBDIR "Lib")
    endif()

    set(FOUND_PATHS "")

    # Search in common Windows Kit locations
    foreach(BASE "C:/Program Files (x86)/Windows Kits/*" "C:/Windows Kits/*" "C:/Program Files/Windows Kits/*")
        file(GLOB SDK_ROOTS "${BASE}")
        foreach(SDK_ROOT ${SDK_ROOTS})
            if(IS_DIRECTORY ${SDK_ROOT})
                # Use GLOB_RECURSE to find the item anywhere under bin or Lib.
                # Then we'll filter by whether the path contains the platform name as a directory component.
                file(GLOB_RECURSE MATCHED_ITEMS "${SDK_ROOT}/${SEARCH_SUBDIR}/**/${ITEM_NAME}")
                foreach(MATCHED_ITEM ${MATCHED_ITEMS})
                    get_filename_component(ITEM_DIR ${MATCHED_ITEM} DIRECTORY)
                    # Check if the platform (e.g., x64, x86) is in the path as a directory component
                    if("${ITEM_DIR}" MATCHES "[\\\\/]${CUBIQ_PLATFORM}([\\\\/]|$)")
                        list(APPEND FOUND_PATHS ${ITEM_DIR})
                    endif()
                endforeach()
            endif()
        endforeach()
    endforeach()

    # Remove duplicates from paths
    list(REMOVE_DUPLICATES FOUND_PATHS)
    unset(FOUND_ITEM CACHE)

    if(TYPE STREQUAL "PROGRAM")
        FIND_PROGRAM(
            FOUND_ITEM
            NAMES ${ITEM_NAME}
            HINTS ${FOUND_PATHS}
            PATHS ${FOUND_PATHS}
        )
    else()
        FIND_LIBRARY(
            FOUND_ITEM
            NAMES ${ITEM_NAME}
            HINTS ${FOUND_PATHS}
            PATHS ${FOUND_PATHS}
        )
    endif()

    set(${ARG_NAME} ${FOUND_ITEM} PARENT_SCOPE)
endfunction()
