add_subdirectory(lib)
add_subdirectory(prog)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif ()
