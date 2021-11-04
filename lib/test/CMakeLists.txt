#unit-tests
add_executable(u_test_static src/unit_tests_consistent.cpp)
target_link_libraries(u_test_static FileUtilsStatic gtest)

add_executable(u_test_dynamic src/unit_tests_parallel.cpp)
target_link_libraries(u_test_dynamic FileUtilsDynamic gtest ${CMAKE_THREAD_LIBS_INIT})

#stress-tests
add_executable(stress_test_d src/stress_test_dynamic.c)
target_link_libraries(stress_test_d FileUtilsDynamic ${CMAKE_DL_LIBS} console_communication)

add_executable(stress_test_s src/stress_test_static.c)
target_link_libraries(stress_test_s FileUtilsStatic console_communication)

add_executable(stress_test_controller src/stress_tests_controller.c)