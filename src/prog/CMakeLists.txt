add_executable(prog main.c)

target_link_libraries(prog waybill)

target_include_directories(prog PUBLIC ${PROJECT_SOURCE_DIR}/src/lib/waybill_manager)
