function(add_certificate_to_target TARGET_NAME)
    FIND_WINSDK_ITEM(SIGNTOOL_EXECUTABLE signtool.exe PROGRAM)
    if(SIGNTOOL_EXECUTABLE)
        set(TIMESTAMP_SERVERS 
            "http://timestamp.digicert.com"
            "http://comodoca.com"
            "http://globalsign.com"
            "http://certum.pl"
            "http://timestamp.acs.microsoft.com"
        )
        
        string(REPLACE ";" "','" SERVERS_ARRAY "${TIMESTAMP_SERVERS}")
        set(SERVERS_ARRAY "'${SERVERS_ARRAY}'")

        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND powershell.exe -Command "$servers = @(${SERVERS_ARRAY}); $signed = $false; foreach ($server in $servers) { Write-Host '[cubiq] Trying timestamp server:' $server; & '${SIGNTOOL_EXECUTABLE}' sign /s MY /n 'ai-vibeqodez' /tr $server /td sha256 /fd SHA256 '$<TARGET_FILE:${TARGET_NAME}>' 2>$null; if ($LASTEXITCODE -eq 0) { $signed = $true; break } }; if (-not $signed) { Write-Warning '[cubiq] All timestamp servers failed or rate-limited. Signing locally without timestamp...'; & '${SIGNTOOL_EXECUTABLE}' sign /s MY /n 'ai-vibeqodez' /fd SHA256 '$<TARGET_FILE:${TARGET_NAME}>' }"
            COMMENT "Signing ${TARGET_NAME} with resilient timestamp fallback..."
            VERBATIM
        )
    else()
        message(WARNING "no SIGNTOOL_EXECUTABLE")
    endif()
endfunction()
