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
    for (int i = 0; i != 10; i++) {
        arr_to_sort[i].amount_weight = (float) i;
    }
    quick_sort_weight(arr_to_sort, 0, 9);
    int count = 0;
    for (int i = 9; i != -1; i--) {
        EXPECT_EQ(arr_to_sort[count].amount_weight, i);
        count++;
    }
    free(arr_to_sort);
}

TEST(SORT_TEST_PRICE, sorting_twenty_numbers) {
    int number = 20;
    auto *arr_to_sort = (product_struct *) (malloc(number * sizeof(product_struct)));
    EXPECT_NE(arr_to_sort, nullptr);
    for (int i = 0; i != 10; i++) {
        arr_to_sort[i].amount_price = (float) i;
    }
    quick_sort_price(arr_to_sort, 0, 9);
    int count = 0;
    for (int i = 9; i != -1; i--) {
        EXPECT_EQ(arr_to_sort[count].amount_price, i);
        count++;
    }
    free(arr_to_sort);
}

TEST(TEST_SPLIT_STRUCT_BY_WEIGTH, spliting_three_structure) {
    EXPECT_EQ(manage_price(nullptr, 0), INPUT_ERROR);

    int amount_of_list = 3;
    auto *waylbill_list = (product_struct *) malloc(amount_of_list * sizeof(product_struct));
    EXPECT_NE(waylbill_list, nullptr);

    product_struct waylbill_first_product = {10, 10, 10.00, 10.00, 100.00, 100.00};
    product_struct waylbill_second_product = {20, 20, 20.00, 20.00, 400.00, 400.00};
    product_struct waylbill_third_product = {30, 10, 20.00, 20.00, 200.00, 200.00};

    waylbill_list[0] = waylbill_first_product;
    waylbill_list[1] = waylbill_second_product;
    waylbill_list[2] = waylbill_third_product;

    EXPECT_EQ(manage_price(waylbill_list, amount_of_list), SUCCESS);
}

TEST(TEST_SPLIT_STRUCT_BY_WEIGTH, spliting_two_structure) {
    EXPECT_EQ(manage_weigth(nullptr, 0), INPUT_ERROR);

    int amount_of_list = 3;
    auto *waylbill_list = (product_struct *) malloc(amount_of_list * sizeof(product_struct));
    EXPECT_NE(waylbill_list, nullptr);

    product_struct waylbill_first_product = {10, 10, 10.00, 10.00, 100.00, 100.00};
    product_struct waylbill_second_product = {20, 20, 20.00, 20.00, 400.00, 400.00};
    product_struct waylbill_third_product = {30, 10, 20.00, 20.00, 200.00, 200.00};

    waylbill_list[0] = waylbill_first_product;
    waylbill_list[1] = waylbill_second_product;
    waylbill_list[2] = waylbill_third_product;

    EXPECT_EQ(manage_price(waylbill_list, amount_of_list), SUCCESS);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
