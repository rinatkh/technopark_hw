file(GLOB SRC
        utils/*.c
        waybill_manager/*.c)

add_library(waybill STATIC ${SRC})