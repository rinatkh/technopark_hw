file(GLOB SRC
        waybill_manager/*.c)

add_library(waybill STATIC ${SRC})