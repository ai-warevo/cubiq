cmake_minimum_required(VERSION 3.15)
project(cubiq_external)

set(CUBIQ_PLATFORM x86)
add_compile_definitions(CUBIQ_PLATFORM="${CUBIQ_PLATFORM}")

include(${CMAKE_SOURCE_DIR}/tools/version/generate_product_version.cmake)

generate_product_version(EXTERNAL_RESOURCES
    NAME "Cubiq External"
    BUNDLE "Cubiq Project"
    COMPANY_NAME "Cubiq Project"
    COMPANY_COPYRIGHT "Cubiq Project (C) Copyright 2026"
    FILE_DESCRIPTION "Cubiq External Cheat"
    ICON "${CMAKE_CURRENT_SOURCE_DIR}/../icon.ico"
    AUTHOR "ai vibeqodez"
    INTERNAL_NAME "cubiq_external.exe"
    ORIGINAL_FILENAME "cubiq_external.exe"
)

add_executable(cubiq_external 
    src/main.cpp
    src/HealthModulator.cpp
    ${EXTERNAL_RESOURCES}
)

target_include_directories(cubiq_external PRIVATE inc ${CMAKE_SOURCE_DIR})

target_link_libraries(cubiq_external PRIVATE cubiq_common cubiq_core_modes_external platform_win32)

include(${CMAKE_SOURCE_DIR}/tools/find_winsdk.cmake)


FIND_WINSDK_ITEM(MT_EXE mt.exe PROGRAM)
if(MT_EXE)
    add_custom_command(TARGET cubiq_external POST_BUILD
        COMMAND "${MT_EXE}" -manifest "${CMAKE_CURRENT_SOURCE_DIR}/manifest.xml" "-outputresource:$<TARGET_FILE:cubiq_external>;#1"
        COMMENT "Embedding manifest into executable using ${MT_EXE}..."
    )
else()
    message(WARNING "mt.exe not found! Manifest will not be embedded.")
endif()

FIND_WINSDK_ITEM(SIGNTOOL_EXECUTABLE signtool.exe PROGRAM)
if(SIGNTOOL_EXECUTABLE)
    set(TIMESTAMP_SERVERS 
        "http://timestamp.digicert.com"
        "http://comodoca.com"
        "http://globalsign.com"
        "http://certum.pl"
        "http://timestamp.acs.microsoft.com"
    )
    
    # Объединяем серверы в строку для передачи в PowerShell массив
    string(REPLACE ";" "','" SERVERS_ARRAY "${TIMESTAMP_SERVERS}")
    set(SERVERS_ARRAY "'${SERVERS_ARRAY}'")

    add_custom_command(TARGET cubiq_external POST_BUILD
        COMMAND powershell.exe -Command "$servers = @(${SERVERS_ARRAY}); $signed = $false; foreach ($server in $servers) { Write-Host '[cubiq] Trying timestamp server:' $server; & '${SIGNTOOL_EXECUTABLE}' sign /s MY /n 'ai-vibeqodez' /tr $server /td sha256 /fd SHA256 '$<TARGET_FILE:cubiq_external>' 2>$null; if ($LASTEXITCODE -eq 0) { $signed = $true; break } }; if (-not $signed) { Write-Warning '[cubiq] All timestamp servers failed or rate-limited. Signing locally without timestamp...'; & '${SIGNTOOL_EXECUTABLE}' sign /s MY /n 'ai-vibeqodez' /fd SHA256 '$<TARGET_FILE:cubiq_external>' }"
        COMMENT "Signing cubiq_external.exe with resilient timestamp fallback..."
        VERBATIM
    )
    # add_custom_command(TARGET cubiq_external POST_BUILD
        # http://timestamp.digicert.com
        # COMMAND "${SIGNTOOL_EXECUTABLE}" sign /s MY /n "ai-vibeqodez" /tr "http://timestamp.acs.microsoft.com" /td sha256 /fd SHA256 "$<TARGET_FILE:cubiq_external>"
        # COMMENT "Signing cubiq_external.exe with local developer certificate..."
    #   )
else()
    message(WARNING "no SIGNTOOL_EXECUTABLE")
endif()
