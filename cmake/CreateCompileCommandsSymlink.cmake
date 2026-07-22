function(create_compile_commands_symlink)
    if(CMAKE_EXPORT_COMPILE_COMMANDS)
        execute_process(
            COMMAND
                ${CMAKE_COMMAND} -E create_symlink
                ${CMAKE_BINARY_DIR}/compile_commands.json
                ${CMAKE_SOURCE_DIR}/compile_commands.json
            RESULT_VARIABLE result
        )

        if(NOT result EQUAL 0)
            message(WARNING "Failed to create compile_commands.json symlink")
        endif()
    endif()
endfunction()
