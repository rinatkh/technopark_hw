add_library(FileUtilsStatic STATIC src/file_utils_consistent.c)
target_link_libraries(FileUtilsStatic PUBLIC errors)
target_include_directories(FileUtilsStatic PUBLIC include)

add_library(FileUtilsDynamic SHARED src/file_utilc_parallel.c)
target_link_libraries(FileUtilsStatic PUBLIC errors)
target_include_directories(FileUtilsDynamic PUBLIC include)


