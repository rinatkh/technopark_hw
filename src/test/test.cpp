#include <gtest/gtest.h>

extern "C" {
#include "manager.h"
#include "quick_sort_wb.h"
#include "product_struct.h"
}


TEST(SORT_TEST_WEIGTH, sorting_ten_numbers) {
    int number = 10;
    auto *arr_to_sort = (product_struct *) (malloc(number * sizeof(product_struct)));
    EXPECT_NE(arr_to_sort, nullptr);
    for (int i = number - 1; i != -1; i--) {
        arr_to_sort[i].weight = i;
    }
    quick_sort_weight(arr_to_sort, 0, 9);

    for (int i = 0; i != number; i++) {
        EXPECT_EQ(arr_to_sort[i].weight, i);
    }
    free(arr_to_sort);
}

TEST(SORT_TEST_PRICE, sorting_twenty_numbers) {
    int number = 20;
    auto *arr_to_sort = (product_struct *) (malloc(number * sizeof(product_struct)));
    EXPECT_NE(arr_to_sort, nullptr);
    for (int i = number - 1; i != -1; i--) {
        arr_to_sort[i].weight = i;
    }
    quick_sort_price(arr_to_sort, 0, 9);

    for (int i = 0; i != number; i++) {
        EXPECT_EQ(arr_to_sort[i].weight, i);
    }
    free(arr_to_sort);
}

TEST(TEST_SPLIT_STRUCT_BY_WEIGTH, spliting_three_structure) {
    EXPECT_EQ(manage_price(nullptr, nullptr, nullptr, 0), INPUT_ERROR);

    int amount_of_list = 3;
    auto *waylbill_list = (product_struct *) malloc(amount_of_list * sizeof(product_struct));
    EXPECT_NE(waylbill_list, nullptr);
    auto *first_list = (product_struct *) malloc(2 * sizeof(product_struct));
    EXPECT_NE(first_list, nullptr);
    auto *second_list = (product_struct *) malloc(2 * sizeof(product_struct));
    EXPECT_NE(second_list, nullptr);

    product_struct waylbill_first_product = {10, 10, 10.00, 10.00, 100.00, 100.00};
    product_struct waylbill_second_product = {20, 20, 20.00, 20.00, 400.00, 400.00};
    product_struct waylbill_third_product = {30, 10, 20.00, 20.00, 200.00, 200.00};

    waylbill_list[0] = waylbill_first_product;
    waylbill_list[1] = waylbill_second_product;
    waylbill_list[2] = waylbill_third_product;

    product_struct first_first_product = {10, 10, 10.00, 10.00, 100.00, 100.00};
    product_struct first_second_product = {20, 12, 20.00, 20.00, 240.00, 400.00};

    first_list[0] = first_first_product;
    first_list[1] = first_second_product;

    product_struct second_first_product = {20, 8, 20.00, 20.00, 160.00, 400.00};
    product_struct second_second_product = {30, 10, 20.00, 20.00, 200.00, 200.00};

    second_list[0] = second_first_product;
    second_list[1] = second_second_product;

    auto *first_check = (product_struct *) malloc(sizeof(product_struct));
    auto *second_check = (product_struct *) malloc(sizeof(product_struct));

    EXPECT_NE(first_check, nullptr);
    EXPECT_NE(second_check, nullptr);

    EXPECT_EQ(manage_price(waylbill_list, first_check, second_check, amount_of_list), SUCCESS);
    for (int i = 0; i != 2; i++) {
        EXPECT_EQ(first_list[i].amount_price, first_check[i].amount_price);
        EXPECT_EQ(second_list[i].amount_price, second_check[i].amount_price);
    }
    free(waylbill_list);
    free(first_list);
    free(second_check);
}

TEST(TEST_SPLIT_STRUCT_BY_WEIGTH, spliting_two_structure) {
    EXPECT_EQ(manage_price(nullptr, nullptr, nullptr, 0), INPUT_ERROR);

    int amount_of_list = 2;
    auto *waylbill_list = (product_struct *) malloc(amount_of_list * sizeof(product_struct));
    EXPECT_NE(waylbill_list, nullptr);
    auto *first_list = (product_struct *) malloc(sizeof(product_struct));
    EXPECT_NE(first_list, nullptr);
    auto *second_list = (product_struct *) malloc(sizeof(product_struct));
    EXPECT_NE(second_list, nullptr);

    product_struct waylbill_first_product = {10, 10, 10.00, 10.00, 100.00, 100.00};
    product_struct waylbill_second_product = {20, 10, 10.00, 10.00, 100.00, 100.00};

    waylbill_list[0] = waylbill_first_product;
    waylbill_list[1] = waylbill_second_product;

    product_struct first_first_product = {10, 10, 10.00, 10.00, 100.00, 100.00};
    first_list[0] = first_first_product;

    product_struct second_first_product = {20, 10, 10.00, 10.00, 100.00, 100.00};
    second_list[0] = second_first_product;

    auto *first_check = (product_struct *) malloc(sizeof(product_struct));
    auto *second_check = (product_struct *) malloc(sizeof(product_struct));

    EXPECT_NE(first_check, nullptr);
    EXPECT_NE(second_check, nullptr);

    EXPECT_EQ(manage_price(waylbill_list, first_check, second_check, amount_of_list), SUCCESS);
    for (int i = 0; i != 2; i++) {
        EXPECT_EQ(first_check[i].amount_price, first_list[i].amount_price);
        EXPECT_EQ(second_check[i].amount_price, second_list[i].amount_price);
    }
    free(waylbill_list);
    free(first_list);
    free(second_check);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
