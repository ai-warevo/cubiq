cmake_minimum_required(VERSION 3.10)
project(cubiq_external)

include(${CMAKE_SOURCE_DIR}/tools/version/generate_product_version.cmake)

generate_product_version(EXTERNAL_RESOURCES
    NAME "Cubiq External"
    BUNDLE "Cubiq Project"
    COMPANY_NAME "Cubiq Project"
    COMPANY_COPYRIGHT "Cubiq Project (C) Copyright 2026"
    FILE_DESCRIPTION "Cubiq External Cheat"
    ICON "${CMAKE_SOURCE_DIR}/app/icon.ico"
)

add_executable(cubiq_external 
    main.cpp
    src/HealthModulator.cpp
    ${EXTERNAL_RESOURCES}
)

target_include_directories(cubiq_external PRIVATE inc ${CMAKE_SOURCE_DIR})

target_link_libraries(cubiq_external PRIVATE cubiq_common)

find_program(MT_EXE NAMES mt.exe PATHS "C:/Program Files (x86)/Windows Kits/10/bin/10.0.26100.0/x64" NO_DEFAULT_PATH)

if(MT_EXE)
    add_custom_command(TARGET cubiq_external POST_BUILD
        COMMAND "${MT_EXE}" -manifest "${CMAKE_CURRENT_SOURCE_DIR}/manifest.xml" "-outputresource:$<TARGET_FILE:cubiq_external>;#1"
        COMMENT "Embedding manifest into executable using ${MT_EXE}..."
    )
else()
    message(WARNING "mt.exe not found! Manifest will not be embedded.")
endif()
