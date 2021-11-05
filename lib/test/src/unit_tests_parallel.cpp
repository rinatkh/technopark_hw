#include <gtest/gtest.h>

extern "C" {
#include "file_utils.h"
#include "errors.h"
}

TEST(FileUtilsTest, FillFile) {
    const char *sequence = "Hello";
    const char *region = "Hello world! Hello world! Hello world! Hello world! Hello world!";
    const char* filename = "test_file";

}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
