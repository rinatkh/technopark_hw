cmake_minimum_required(VERSION 3.6)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_COVERAGE "Build coverage" ON)

project(hw-1 VERSION 0.1.0)

string(APPEND CMAKE_C_FLAGS " -pedantic -Wall -Wextra")

add_subdirectory(tools/gtest)
add_subdirectory(src)

