#include <getopt.h>
#include <malloc.h>

#include "manager.h"
#include "product_struct.h"

int main(int argc, char **argv) {

    int count = count_reading();
    product_struct *waylbill_list = (product_struct *) malloc(count * sizeof(product_struct));

    if (!waylbill_list) {
        return -1;
    }

    product_struct *first_waybill = (product_struct *) malloc(sizeof(product_struct));
    product_struct *second_waybill = (product_struct *) malloc(sizeof(product_struct));

    if ((!first_waybill) || (!second_waybill)) {
        return -1;
    }
    structs_reading(waylbill_list, count);

    int i;
    while ((i = getopt(argc, argv, "pw")) != -1) {
        switch (i) {
            case 'p':
                manage_price(waylbill_list, first_waybill, second_waybill, count);
                for (int i = 0; i < 1; i++) {
                    printf("\n%d: Vendor code: %d\tAmount: %i\tTotal price: %f\tTotal weight: %f", i + 1, first_waybill[i].vendor_code,
                           first_waybill[i].amount,
                           first_waybill[i].amount_price,
                           first_waybill[i].amount_weight);
                }

                free(waylbill_list);
                free(first_waybill);
                free(second_waybill);
                break;

            case 'w':
                manage_weigth(waylbill_list, first_waybill, second_waybill, count);
                free(waylbill_list);
                free(first_waybill);
                free(second_waybill);
                break;

            default:
                break;
        }
    }
    return 0;
}


