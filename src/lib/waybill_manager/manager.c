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

static product_struct struct_reading(int number_of_position) {
    product_struct product;

    printf("\t%d product:\n", number_of_position + 1);

    printf("Product vendor code: \n");
    while ((scanf("%d", &product.vendor_code) != 1) || (product.vendor_code <= 0)) {
        printf(" !Enter a POSITIVE INTEGER product vendor code: \n");
        while (getchar() != '\n');
    };

    printf("An amount of this product: \n");
    while ((scanf(" %d", &product.amount) != 1) || (product.amount < 0)) {
        printf(" !Enter a POSITIVE INTEGER number of products: \n");
        while (getchar() != '\n');
    };

    printf("Price of this product: \n");
    while (scanf("%f", &product.price) != 1) {
        printf(" !Enter a correct product price: \n");
        while (getchar() != '\n');
    };

    printf("Weight of this product: \n");
    while (scanf("%f", &product.weight) != 1) {
        printf(" !Enter a correct product weight: \n");
        while (getchar() != '\n');
    };
    product.amount_price = (float) (product.amount * product.price);
    product.amount_weight = (float) (product.amount * product.weight);

    return product;
}

void structs_reading(product_struct *waybill_list, int count_of_position) {
    if (waybill_list) {
        for (int i = 0; i < count_of_position; i++) {
            waybill_list[i] = struct_reading(i);
        }
    }
    else {
        printf("INPUT FOR READING ERROR");
    }

}

static void new_waybill_output(int count, const product_struct *waybill) {

    printf("\n\t New waybill:\n");
    float sum_price = 0;
    float sum_weigth = 0;
    for (int i = 0; i < count; i++) {
        printf("\n%d: Vendor code: %d\tAmount: %i\tTotal price: %f\tTotal weight: %f", i + 1, waybill[i].vendor_code, waybill[i].amount, waybill[i].amount_price,
               waybill[i].amount_weight);
        sum_price += waybill[i].amount_price;
        sum_weigth += waybill[i].amount_weight;
    }
    printf("\nWaybill price: %f\tWaybill weight: %f", sum_price, sum_weigth);
    printf("\n");
}

static void
split_by_number_equal(const product_struct *waybill, product_struct *first_waybill, product_struct *second_waybill, int split_number,
                      int waybill_len) {
    for (int i = 0; i != split_number + 1; i++) {
        first_waybill[i] = waybill[i];
    }
    for (int i = split_number + 1; i != waybill_len; i++) {
        second_waybill[i - split_number - 1] = waybill[i];
    }
}

static void
split_by_number_not_equal_weigth(const product_struct *waybill, product_struct *first_waybill, product_struct *second_waybill, int split_number,
                                 int waybill_len, float current_sum, float middle) {
    product_struct last_for_first = waybill[split_number];
    product_struct first_for_second = waybill[split_number];

    int current_amount = 1;
    for (int i = 0; i != waybill[split_number].amount; i++) {
        current_sum += waybill[split_number].weight;
        if (current_sum > middle) {
            last_for_first.amount = current_amount - 1;
            last_for_first.amount_weight = (float) (last_for_first.amount * last_for_first.weight);

            first_for_second.amount = waybill[split_number].amount - current_amount + 1;
            first_for_second.amount_weight = (float) (first_for_second.amount * first_for_second.weight);
            break;

        } else if (current_sum == middle) {
            last_for_first.amount = current_amount;
            last_for_first.amount_weight = (float) (last_for_first.amount * last_for_first.weight);

            first_for_second.amount = waybill[split_number].amount - current_amount;
            first_for_second.amount_weight = (float) (first_for_second.amount * first_for_second.weight);
            break;

        }
        current_amount++;
    }

    for (int i = 0; i != split_number; i++) {
        first_waybill[i] = waybill[i];
    }
    first_waybill[split_number] = last_for_first;
    second_waybill[0] = first_for_second;

    for (int i = split_number + 1; i != waybill_len; i++) {
        second_waybill[i - split_number] = waybill[i];
    }
}

static void
split_by_number_not_equal_price(const product_struct *waybill, product_struct *first_waybill, product_struct *second_waybill, int split_number,
                                int waybill_len, float current_sum, float middle) {
    product_struct last_for_first = waybill[split_number];
    product_struct first_for_second = waybill[split_number];

    int current_amount = 1;
    for (int i = 0; i != waybill[split_number].amount; i++) {
        current_sum += waybill[split_number].weight;
        if (current_sum > middle) {
            last_for_first.amount = current_amount - 1;
            last_for_first.amount_price = (float) (last_for_first.amount * last_for_first.price);

            first_for_second.amount = waybill[split_number].amount - current_amount + 1;
            first_for_second.amount_price = (float) (first_for_second.amount * first_for_second.price);
            break;

        } else if (current_sum == middle) {
            last_for_first.amount = current_amount;
            last_for_first.amount_price = (float) (last_for_first.amount * last_for_first.price);

            first_for_second.amount = waybill[split_number].amount - current_amount;
            first_for_second.amount_price = (float) (first_for_second.amount * first_for_second.price);
            break;
        }
        current_amount++;
    }

    for (int i = 0; i != split_number; i++) {
        first_waybill[i] = waybill[i];
    }
    first_waybill[split_number] = last_for_first;
    second_waybill[0] = first_for_second;

    for (int i = split_number + 1; i != waybill_len; i++) {
        second_waybill[i - split_number] = waybill[i];
    }
}

waybill_errors manage_weigth(product_struct *waybill, int waybill_len) {
    if (!waybill) {
        return INPUT_ERROR;
    }

    quick_sort_weight(waybill, 0, waybill_len - 1);
    product_struct *first_waybill = NULL;
    product_struct *second_waybill = NULL;

    float sum = 0;
    for (int i = 0; i != waybill_len; i++) {
        sum += waybill[i].amount_weight;
    }

    float middle = sum / 2;
    float current_sum = 0;
    float prev_curren_sum = 0;
    for (int i = 0; i != waybill_len; i++) {
        current_sum += waybill[i].amount_weight;
        if (current_sum > middle) {
            first_waybill = (product_struct *) (malloc((i + 1) * sizeof(product_struct)));
            if (!first_waybill) {
                return MEMORY_ERROR;
            }
            second_waybill = (product_struct *) (malloc((waybill_len - i) * sizeof(product_struct)));
            if (!second_waybill) {
                return MEMORY_ERROR;
            }
            split_by_number_not_equal_weigth(waybill, first_waybill, second_waybill, i, waybill_len, prev_curren_sum, middle);
            new_waybill_output(i + 1, first_waybill);
            new_waybill_output(waybill_len - i, second_waybill);
            free(first_waybill);
            free(second_waybill);
            break;
        } else if (current_sum == middle) {
            first_waybill = (product_struct *) (malloc((i + 1) * sizeof(product_struct)));
            if (!first_waybill) {
                return MEMORY_ERROR;
            }
            second_waybill = (product_struct *) (malloc((waybill_len - i - 1) * sizeof(product_struct)));
            if (!second_waybill) {
                return MEMORY_ERROR;
            }
            split_by_number_equal(waybill, first_waybill, second_waybill, i, waybill_len);
            new_waybill_output(i + 1, first_waybill);
            new_waybill_output(waybill_len - i - 1, second_waybill);
            free(first_waybill);
            free(second_waybill);
            break;
        }
        prev_curren_sum = current_sum;
    }
    return SUCCESS;
}

waybill_errors manage_price(product_struct *waybill, int waybill_len) {
    if (!waybill) {
        return INPUT_ERROR;
    }

    quick_sort_weight(waybill, 0, waybill_len - 1);
    product_struct *first_waybill = NULL;
    product_struct *second_waybill = NULL;

    float sum = 0;
    for (int i = 0; i != waybill_len; i++) {
        sum += waybill[i].amount_price;
    }

    float middle = sum / 2;
    float current_sum = 0;
    float prev_curren_sum = 0;
    for (int i = 0; i != waybill_len; i++) {
        current_sum += waybill[i].amount_price;
        if (current_sum > middle) {
            first_waybill = (product_struct *) (malloc((i + 1) * sizeof(product_struct)));
            if (!first_waybill) {
                return MEMORY_ERROR;
            }
            second_waybill = (product_struct *) (malloc((waybill_len - i) * sizeof(product_struct)));
            if (!second_waybill) {
                return MEMORY_ERROR;
            }
            split_by_number_not_equal_price(waybill, first_waybill, second_waybill, i, waybill_len, prev_curren_sum, middle);
            new_waybill_output(i + 1, first_waybill);
            new_waybill_output(waybill_len - i, second_waybill);
            free(first_waybill);
            free(second_waybill);
            break;
        } else if (current_sum == middle) {
            first_waybill = (product_struct *) (malloc((i + 1) * sizeof(product_struct)));
            if (!first_waybill) {
                free(first_waybill);
                return MEMORY_ERROR;
            }
            second_waybill = (product_struct *) (malloc((waybill_len - i - 1) * sizeof(product_struct)));
            if (!second_waybill) {
                free(first_waybill);
                return MEMORY_ERROR;
            }
            split_by_number_equal(waybill, first_waybill, second_waybill, i, waybill_len);
            new_waybill_output(i + 1, first_waybill);
            new_waybill_output(waybill_len - i - 1, second_waybill);
            free(first_waybill);
            free(second_waybill);
            break;
        }
        prev_curren_sum = current_sum;
    }
    return SUCCESS;
}
