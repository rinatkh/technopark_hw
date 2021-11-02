set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads)

add_library(FileUtilsStatic STATIC src/file_utils_consistent.c)
target_link_libraries(FileUtilsStatic PUBLIC errors)
target_include_directories(FileUtilsStatic PUBLIC include)

add_library(FileUtilsDynamic SHARED src/file_utilc_parallel.c)
target_link_libraries(FileUtilsDynamic PUBLIC errors
                                  PUBLIC pthread)
target_include_directories(FileUtilsDynamic PUBLIC include)


