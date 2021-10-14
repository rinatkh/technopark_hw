#ifndef PRODUCT_STRUCT_H
#define PRODUCT_STRUCT_H

#define FLAG_WEIGTH 1
#define FLAG_PRICE 2

typedef struct product_struct_t {
    int vendor_code;
    int amount;
    float price;
    float weight;
    float amount_price;
    float amount_weight;
} product_struct;

#endif //PRODUCT_STRUCT_H
