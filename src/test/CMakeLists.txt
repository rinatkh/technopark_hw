add_executable(test test.cpp)

target_link_libraries(test gtest waybill)
target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/src/lib/waybill_manager)
