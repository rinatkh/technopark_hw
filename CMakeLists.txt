cmake_minimum_required(VERSION 3.13)

project(Homework2)

add_compile_options(-Wall -Wextra -pedantic)
find_package(Threads)

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


add_executable(prog src/main.c)
target_link_libraries(prog console_communication)

add_subdirectory(lib)
option(WITH_STATIC_LIB "Run with consistent lib" OFF)
if(WITH_STATIC_LIB)
    target_link_libraries(prog FileUtilsStatic)
endif()

option(WITH_SHARED_LIB "Run with dynamic lib" ON)
if(WITH_SHARED_LIB)
    target_link_libraries(prog FileUtilsDynamic pthread)
endif()