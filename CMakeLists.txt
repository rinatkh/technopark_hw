cmake_minimum_required(VERSION 3.13)

project(Homework2)

add_compile_options(-Wall -Wextra -pedantic)

option(WITH_COVERAGE "Add coverage estimation")
if(WITH_COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

option(WITH_SANITIZERS "Add address sanitizer")
if(WITH_SANITIZERS)
    add_compile_options(-fno-omit-frame-pointer -fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

option(WITH_TESTS "Build tests" ON)
if(WITH_TESTS OR WITH_SANITIZERS OR WITH_COVERAGE)
    set(BUILD_TESTS ON)
    enable_testing()
    add_subdirectory(tools/gtest)
endif()

add_subdirectory(lib)

add_executable(prog src/main.c)

option(WITH_FILE_STATIC "Run with consistent lib" ON)
if(WITH_FILE_STATIC)
    SET(BUILD_WITH_STATIC ON)
    SET(BUILD_WITH_DYNAMIC OFF)
    target_link_libraries(prog FileUtilsStatic)
endif()

option(WITH_FILE_DYNAMIC "Run with threads lib" OFF)
if(WITH_FILE_DYNAMIC)
    SET(BUILD_WITH_STATIC OFF)
    SET(BUILD_WITH_DYNAMIC ON)
    target_link_libraries(prog FileUtilsDynamic pthread)
endif()