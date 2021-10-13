cmake_minimum_required(VERSION 3.6)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

project(hw-1 VERSION 0.1.0)

string(APPEND CMAKE_C_FLAGS " -pedantic -Wall -Wextra")

add_subdirectory(tools/gtest)
add_subdirectory(src)

