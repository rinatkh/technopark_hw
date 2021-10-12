find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(test test.cpp)

target_link_libraries(test ${GTEST_LIBRARIES} waybill)
target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/src/lib/waybill_manager)
