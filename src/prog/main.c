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

    structs_reading(waylbill_list, count);

    int i;
    while ((i = getopt(argc, argv, "pw")) != -1) {
        switch (i) {
            case 'p':
                manage_price(waylbill_list, count);
                free(waylbill_list);
                break;

            case 'w':
                manage_weigth(waylbill_list, count);
                free(waylbill_list);
                break;

            default:
                break;
        }
    }
    return 0;
}


