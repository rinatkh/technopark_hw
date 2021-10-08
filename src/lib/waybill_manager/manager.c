#include <malloc.h>
#include <string.h>

#include "manager.h"
#include "product_struct.h"
#include "quick_sort_wb.h"

int count_reading() {
    int count = 0;
    printf("\nEnter an amount of waybill positions: \n");
    while ((scanf("%d", &count) != 1) || (count <= 0)) {
        printf("Enter a POSITIVE INTEGER amount of waybill positions: \n");
        while (getchar() != '\n');
    };
    return count;
}

product_struct *struct_reading(int count_of_position) {
    product_struct *product = ((product_struct *) malloc(count_of_position * sizeof(product_struct *)));

    printf("%d product:\n", count_of_position);

    printf("%i product vendor code: \n", count_of_position);
    while ((scanf("%d", &product->vendor_code) != 1) || (product->vendor_code <= 0)) {
        printf(" !Enter a POSITIVE INTEGER product vendor code: \n");
        while (getchar() != '\n');
    };

    printf("%i amount of this product: \n", count_of_position);
    while ((scanf(" %d", &product->amount) != 1) || (product->amount < 0)) {
        printf(" !Enter a POSITIVE INTEGER number of products: \n");
        while (getchar() != '\n');
    };

    printf("%i price of this product: \n", count_of_position);
    while (scanf("%f", &product->price) != 1) {
        printf(" !Enter a correct product price: \n");
        while (getchar() != '\n');
    };

    printf("%i weight of this product: \n", count_of_position);
    while (scanf("%f", &product->weight) != 1) {
        printf(" !Enter a correct product weight: \n");
        while (getchar() != '\n');
    };
    product->amount_price = (float) product->amount * product->price;
    product->amount_weight = (float) product->amount * product->weight;

    return product;
}


waybill_errors manage_weigth(product_struct **waybill, int waybill_len) {
    if (!waybill) {
        return INPUT_ERROR;
    }

    quick_sort_weight(waybill, 0, waybill_len - 1);
    product_struct **first_waybill = NULL;
    product_struct **second_waybill = NULL;

    float sum = 0;
    for (int i = 0; i != waybill_len; i++) {
        sum += waybill[i]->amount_weight;
    }

    float middle = sum / 2;
    float current_sum = 0;
    for (int i = 0; i != waybill_len; i++) {
        current_sum += waybill[i]->amount_weight;
        if (current_sum > middle) {
            first_waybill = (product_struct *) (malloc(i * sizeof(product_struct *)));
            second_waybill = (product_struct *) (malloc((waybill_len - i + 1) * sizeof(product_struct *)));
            break;
        } else if (current_sum == middle) {
            first_waybill = (product_struct **) (malloc(i * sizeof(product_struct *)));
            second_waybill = (product_struct **) (malloc((waybill_len - i) * sizeof(product_struct *)));
            memmove(first_waybill, waybill, i * sizeof(product_struct));
            for (int k = 0; k < i; ++k) {
                printf("%i\n", first_waybill[k]->vendor_code);
            }
            memmove(second_waybill, waybill + i + 1, i * sizeof(product_struct));
            break;
        }
    }
    return SUCCESS;
}

waybill_errors manage_price(product_struct *waybill, int waybill_len) {

}
