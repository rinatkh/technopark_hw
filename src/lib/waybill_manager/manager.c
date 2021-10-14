#include <malloc.h>
#include <unistd.h>
#include <poll.h>
#include <stdio.h>

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
    struct pollfd revents = {STDIN_FILENO, POLLIN | POLLPRI, POLLIN | POLLPRI  };
    if (poll(&revents, 1, 2000)) {
        printf("\t%d product:\n", number_of_position + 1);
        printf("Product vendor code: \n");

        while ((scanf("%d", &product.vendor_code) != 1) ||
               (product.vendor_code <= 0)) {
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
    }
    product.amount_price = (float) (product.amount) * product.price;
    product.amount_weight = (float) (product.amount) * product.weight;
    return product;
}

waybill_errors
structs_reading(product_struct *waybill_list, int count_of_position) {
    if (waybill_list) {
        for (int i = 0; i < count_of_position; i++) {
            waybill_list[i] = struct_reading(i);
        }
        return SUCCESS;
    } else {
        return INPUT_ERROR;
    }
}

void new_waybill_output(int count, const product_struct *waybill) {
    if (waybill) {
        printf("\n\t New waybill:\n");
        float sum_price = 0;
        float sum_weigth = 0;
        for (int i = 0; i < count; i++) {
            printf("\n%d: Vendor code: %d\tAmount: %i\tTotal price: %f\tTotal weight: %f",
                   i + 1, waybill[i].vendor_code, waybill[i].amount,
                   waybill[i].amount_price,
                   waybill[i].amount_weight);
            sum_price += waybill[i].amount_price;
            sum_weigth += waybill[i].amount_weight;
        }
        printf("\nWaybill price: %f\tWaybill weight: %f", sum_price,
               sum_weigth);
        printf("\n");
    } else {
        printf("OUTPUT of new waybill is error");
    }
}

static void
split_by_number_equal(const product_struct *waybill,
                      product_struct *first_waybill,
                      product_struct *second_waybill, int split_number,
                      int waybill_len) {
    for (int i = 0; i != split_number + 1; i++) {
        first_waybill[i] = waybill[i];
    }
    for (int i = split_number + 1; i != waybill_len; i++) {
        second_waybill[i - split_number - 1] = waybill[i];
    }
}

static void
split_by_number_not_equal(const product_struct *waybill,
                          product_struct *first_waybill,
                          product_struct *second_waybill,
                          int split_number,
                          int waybill_len, float current_sum,
                          float middle, int flag) {
    product_struct last_for_first = waybill[split_number];
    product_struct first_for_second = waybill[split_number];

    int current_amount = 1;
    for (int i = 0; i != waybill[split_number].amount; i++) {
        current_sum += waybill[split_number].weight;
        if (current_sum > middle) {
            last_for_first.amount = current_amount - 1;
            last_for_first.amount_price =
                    (float) (last_for_first.amount) * last_for_first.price;
            if (flag == FLAG_WEIGTH) {
                first_for_second.amount =
                        waybill[split_number].amount - current_amount + 1;
                first_for_second.amount_weight =
                        (float) (first_for_second.amount) *
                        first_for_second.weight;
            } else if (flag == FLAG_PRICE) {
                first_for_second.amount =
                        waybill[split_number].amount - current_amount + 1;
                first_for_second.amount_price =
                        (float) (first_for_second.amount) *
                        first_for_second.price;
            }
            break;

        } else if (current_sum == middle) {
            last_for_first.amount = current_amount;
            first_for_second.amount =
                    waybill[split_number].amount - current_amount;
            if (flag == FLAG_WEIGTH) {

                last_for_first.amount_weight =
                        (float) (last_for_first.amount) * last_for_first.price;
                first_for_second.amount_weight =
                        (float) (first_for_second.amount) *
                        first_for_second.weight;
            } else if (flag == FLAG_PRICE) {
                last_for_first.amount_price =
                        (float) (last_for_first.amount) * last_for_first.price;
                first_for_second.amount_price =
                        (float) (first_for_second.amount) *
                        first_for_second.price;
            }
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

static float sum_(product_struct *waybill, int flag, int waybill_len) {
    float sum = 0;
    if (flag == FLAG_WEIGTH) {
        for (int i = 0; i != waybill_len; i++) {
            sum += waybill[i].amount_weight;
        }
    }
    if (flag == FLAG_PRICE) {
        for (int i = 0; i != waybill_len; i++) {
            sum += waybill[i].amount_price;
        }
    }
    return sum;
}

waybill_errors manage(product_struct *waybill, int waybill_len,
                      int flag) {
    if (!waybill) {
        return INPUT_ERROR;
    }

    quick_sort(waybill, 0, waybill_len - 1, flag, change_position);

    float sum = sum_(waybill, flag, waybill_len);

    float middle = sum / 2;
    float current_sum = 0;
    float prev_curren_sum = 0;

    product_struct *first_waybill = NULL, *second_waybill = NULL;
    int first_length = 0, second_length = 0;
    for (int i = 0; i != waybill_len; i++) {
        if (flag == FLAG_PRICE) {
            current_sum += waybill[i].amount_price;
        } else if (flag == FLAG_WEIGTH) {
            current_sum += waybill[i].amount_weight;
        }

        if (current_sum >= middle) {
            first_waybill = (product_struct *) (malloc(
                    (i + 1) * sizeof(product_struct)));
            first_length = i + 1;
            if (!first_waybill) {
                return MEMORY_ERROR;
            }
        }
        if (current_sum > middle) {
            second_waybill = (product_struct *) (malloc(
                    (waybill_len - i) * sizeof(product_struct)));
            second_length = waybill_len - i;
            if (!second_waybill) {
                free(first_waybill);
                return MEMORY_ERROR;
            }

            split_by_number_not_equal(waybill, first_waybill,
                                      second_waybill, i, waybill_len,
                                      prev_curren_sum, middle, flag);
            break;
        } else if (current_sum == middle) {
            second_waybill = (product_struct *) (malloc(
                    (waybill_len - i - 1) * sizeof(product_struct)));
            second_length = waybill_len - i - 1;
            if (!second_waybill) {
                free(first_waybill);
                return MEMORY_ERROR;
            }
            split_by_number_equal(waybill, first_waybill, second_waybill, i,
                                  waybill_len);
            break;
        }
        prev_curren_sum = current_sum;
    }
    new_waybill_output(first_length, first_waybill);
    new_waybill_output(second_length, second_waybill);
    if (first_waybill) {
        free(first_waybill);
    }
    if (second_waybill) {
        free(second_waybill);
    }
    return SUCCESS;
}

