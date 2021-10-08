#include <getopt.h>
#include <stdio.h>
#include <malloc.h>

#include "manager.h"
#include "product_struct.h"

int main(int argc, char **argv) {

    int count = count_reading();
    product_struct **waylbil_list = (product_struct **) malloc(count * sizeof(waylbil_list));
    for (int i = 0; i < count; i++) {
        waylbil_list[i] = struct_reading(count);
    }

    int i;
    while ((i = getopt(argc, argv, "pw")) != -1) {
        switch (i) {
            case 'p':
//                manage_price(waybill, count);
                break;

            case 'w':
                manage_weigth(waylbil_list, count);
                break;

            default:
                break;
        }
    }
    return 0;
}


