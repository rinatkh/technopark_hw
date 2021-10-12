#ifndef HW_1_MANAGER_H
#define HW_1_MANAGER_H

#include "product_struct.h"

typedef enum {
    SUCCESS,
    INPUT_ERROR,
    MEMORY_ERROR
} waybill_errors;

int count_reading();

void structs_reading(product_struct *waybill_list, int count_of_position);

waybill_errors manage_weigth(product_struct *waybill, int waybill_len);

waybill_errors manage_price(product_struct *waybill, int waybill_len);

#endif //HW_1_MANAGER_H
