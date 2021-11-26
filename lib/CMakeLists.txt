add_subdirectory(file_utils)
add_subdirectory(errors)
add_subdirectory(console_communication)

if (BUILD_TESTS)
    add_subdirectory(test)
endif ()