#ifndef HW_1_QUICK_SORT_WB_H
#define HW_1_QUICK_SORT_WB_H

#include "product_struct.h"

void change_position(int flag, int *left, int *right, product_struct *arr);

void quick_sort(product_struct *arr, int first, int last, int flag,
                void (*equal_what)(int, int *, int *, product_struct *));

#endif //HW_1_QUICK_SORT_WB_H
