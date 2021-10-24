#ifndef HW_1_MANAGER_H
#define HW_1_MANAGER_H

#include "product_struct.h"

typedef enum {
    SUCCESS,
    INPUT_ERROR,
    MEMORY_ERROR
} waybill_errors;

int count_reading();

void new_waybill_output(int count, const product_struct *waybill);

waybill_errors
structs_reading(product_struct *waybill_list, int count_of_position);

waybill_errors manage(product_struct *waybill, int waybill_len,
                      int flag);

#endif //HW_1_MANAGER_H
