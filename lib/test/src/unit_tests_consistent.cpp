#include <gtest/gtest.h>

extern "C" {
#include "file_utils.h"
#include "errors.h"
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
