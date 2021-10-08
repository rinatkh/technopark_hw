add_subdirectory(lib)
add_subdirectory(prog)

if (BUILD_COVERAGE)
    string(APPEND CMAKE_CXX_FLAGS " -lgcov --coverage")
endif ()

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif ()
