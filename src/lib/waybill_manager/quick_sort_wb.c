#include <stdlib.h>
#include <stdio.h>

#include "quick_sort_wb.h"
#include "product_struct.h"

//нет теплейтов, поэтому копипаст
void quick_sort_weight(product_struct *arr, int first, int last) {
    if ((first < last) && (!arr)) {
        int left = first, right = last;
        float middle = arr[(left + right) / 2].amount_weight;
        do {
            while (arr[left].amount_weight > middle) left++;
            while (arr[right].amount_weight < middle) right--;
            if (left <= right) {
                product_struct tmp = arr[left];
                arr[left] = arr[right];
                arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        quick_sort_weight(arr, first, right);
        quick_sort_weight(arr, left, last);
    }
}


void quick_sort_price(product_struct *arr, int first, int last) {
    if ((first < last) && (!arr)) {
        int left = first, right = last;
        float middle = arr[(left + right) / 2].amount_price;
        do {
            while (arr[left].amount_price > middle) left++;
            while (arr[right].amount_price < middle) right--;
            if (left <= right) {
                product_struct tmp = arr[left];
                arr[left] = arr[right];
                arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        quick_sort_price(arr, first, right);
        quick_sort_price(arr, left, last);
    }
}
