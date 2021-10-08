#ifndef HW_1_MANAGER_H
#define HW_1_MANAGER_H

#include "product_struct.h"

typedef enum {
    SUCCESS,
    INPUT_ERROR,
    WAYBILL_SPLIT_ERROR
} waybill_errors;

waybill_errors split_weigth(product_struct *waybill, product_struct *first_waybill, product_struct *second_waybill);

waybill_errors split_price(product_struct *waybill, product_struct *first_waybill, product_struct *second_waybill);

#endif //HW_1_MANAGER_H
