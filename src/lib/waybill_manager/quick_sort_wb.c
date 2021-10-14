#include <stddef.h>

#include "quick_sort_wb.h"
#include "product_struct.h"

void change_position(int flag, int *left, int *right, product_struct *arr) {

    float middle_price = arr[(*left + *right) / 2].amount_price;
    float middle_weight = arr[(*left + *right) / 2].amount_weight;

    do {
        if (flag == FLAG_PRICE) {
            while (arr[*left].amount_price > middle_price) (*left) += 1;
            while (arr[*right].amount_price < middle_price) (*right) -= 1;
        }
        if (flag == FLAG_WEIGTH) {
            while (arr[*left].amount_weight > middle_weight) (*left) += 1;
            while (arr[*right].amount_weight < middle_weight) (*right) -= 1;
        }

        if (*left <= *right) {
            product_struct tmp = arr[*left];
            arr[*left] = arr[*right];
            arr[*right] = tmp;
            (*left) += 1;
            (*right) -= 1;
        }
    } while (*left <= *right);
}


void quick_sort(product_struct *arr, int first, int last, int flag,
                void (*equal_what)(int, int *, int *, product_struct *)) {
    if ((first < last) && (arr != NULL)) {
        int left = first, right = last;

        equal_what(flag, &left, &right, arr);

        quick_sort(arr, first, right, flag, equal_what);
        quick_sort(arr, left, last, flag, equal_what);
    }
}


