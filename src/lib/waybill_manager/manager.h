#ifndef HW_1_MANAGER_H
#define HW_1_MANAGER_H

#include "product_struct.h"

typedef enum {
    SUCCESS,
    INPUT_ERROR,
    WAYBILL_SPLIT_ERROR
} waybill_errors;

int count_reading();

product_struct *struct_reading(int count_of_position);

waybill_errors manage_weigth(product_struct **waybill, int waybill_len);

waybill_errors manage_price(product_struct *waybill, int waybill_len);

#endif //HW_1_MANAGER_H
