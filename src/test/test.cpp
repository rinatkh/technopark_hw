#include <gtest/gtest.h>

extern "C" {
#include "manager.h"
#include "quick_sort_wb.h"
#include "product_struct.h"
}


TEST(SORT_TEST_WEIGTH, sorting_ten_numbers) {
    int number = 10;
    auto *arr_to_sort = (product_struct *) (malloc(number * sizeof(product_struct)));
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
    for (int i = number - 1; i != -1; i--) {
        arr_to_sort[i].weight = i;
    }
    quick_sort_price(arr_to_sort, 0, 9);

    for (int i = 0; i != number; i++) {
        EXPECT_EQ(arr_to_sort[i].weight, i);
    }
    free(arr_to_sort);
}

TEST(TEST_FILLED_STRUCT, filling_by_two_structures) {

}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
