// "Copyright 2021 <RINAT>"
#include <getopt.h>
#include <malloc.h>
#include <stddef.h>

#include "manager.h"
#include "product_struct.h"

int main(int argc, char **argv) {

    int count = count_reading();
    product_struct *waylbill_list = (product_struct *) malloc(
            count * sizeof(product_struct));

    if (waylbill_list == NULL) {
        printf("INPUT FOR READING ERROR");
        return -1;
    }
    if (structs_reading(waylbill_list, count) == INPUT_ERROR) {
        return -1;
    }

    int i;
    while ((i = getopt(argc, argv, "pw")) != -1) {
        switch (i) {
            case 'p':

                manage(waylbill_list, count, FLAG_PRICE);
                if (waylbill_list) {
                    free(waylbill_list);
                }
                break;

            case 'w':

                manage(waylbill_list, count, FLAG_WEIGTH);
                if (waylbill_list) {
                    free(waylbill_list);
                }
                break;

            default:
                break;
        }
    }
    return 0;
}


