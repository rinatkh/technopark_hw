#include <gtest/gtest.h>
#include <malloc.h>

extern "C" {
#include "file_utils.h"
#include "errors.h"
}

TEST(FileUtilsTest, findSequence) {

    const char sequence1[] = "Hello";
    const char *region = "Hello world! Hello world! Hello world! Hello world! Hello world!";
    const unsigned long file_size = 64;
    ASSERT_EQ(find_sequence(nullptr, nullptr, file_size), -1);
    ASSERT_EQ(find_sequence(nullptr, region, file_size), -1);
    ASSERT_EQ(find_sequence(sequence1, nullptr, file_size), -1);
    ASSERT_EQ(find_sequence(sequence1, region, file_size), 5);

    const char sequence2[] = "l";
    ASSERT_EQ(find_sequence(sequence2, region, file_size), 15);

}

TEST(FileUtilsTest, find_in_file_sequences) {

    const unsigned long file_size = 98676000;
    const char *filename = "../../../files/100mb.txt";
    const char *wrong_filename = "text";
    const int count_of_sequences = 15;

    char **sequences = (char **) malloc(count_of_sequences * sizeof(char *));
    EXPECT_NE(sequences, nullptr);

    sequences[0] = (char *) "announced";
    sequences[1] = (char *) "disapperared";
    sequences[2] = (char *) "discreetly";
    sequences[3] = (char *) "about";
    sequences[4] = (char *) "tree";
    sequences[5] = (char *) "home";
    sequences[6] = (char *) "Hello";
    sequences[7] = (char *) "World";
    sequences[8] = (char *) "?!";
    sequences[9] = (char *) "dream";
    sequences[10] = (char *) "errors";
    sequences[11] = (char *) "qwerty";
    sequences[12] = (char *) "tag";
    sequences[13] = (char *) "unit";
    sequences[14] = (char *) "CHAPTER";

    int *amount_of_coindencess = (int *) malloc(count_of_sequences * sizeof(int));

    ASSERT_EQ(find_in_file_sequences(nullptr, file_size, (const char **) sequences,
                                     count_of_sequences, amount_of_coindencess), ERROR_INPUT);
    ASSERT_EQ(find_in_file_sequences(filename, file_size, nullptr, count_of_sequences,
                                     amount_of_coindencess), ERROR_INPUT);
    ASSERT_EQ(find_in_file_sequences(filename, file_size, (const char **) sequences,
                                     count_of_sequences, nullptr), ERROR_INPUT);

    ASSERT_EQ(find_in_file_sequences(wrong_filename, file_size, (const char **) sequences,
                                     count_of_sequences, amount_of_coindencess), ERROR_FILE);
    ASSERT_EQ(find_in_file_sequences(filename, file_size, (const char **) sequences,
                                     count_of_sequences, amount_of_coindencess), SUCCESS);

    ASSERT_EQ(amount_of_coindencess[0], 1440);
    ASSERT_EQ(amount_of_coindencess[1], 0);
    ASSERT_EQ(amount_of_coindencess[2], 720);
    ASSERT_EQ(amount_of_coindencess[3], 51120);
    ASSERT_EQ(amount_of_coindencess[4], 14040);
    ASSERT_EQ(amount_of_coindencess[5], 10440);
    ASSERT_EQ(amount_of_coindencess[6], 1800);
    ASSERT_EQ(amount_of_coindencess[7], 2520);
    ASSERT_EQ(amount_of_coindencess[8], 0);
    ASSERT_EQ(amount_of_coindencess[9], 5760);
    ASSERT_EQ(amount_of_coindencess[10], 0);
    ASSERT_EQ(amount_of_coindencess[11], 0);
    ASSERT_EQ(amount_of_coindencess[12], 2880);
    ASSERT_EQ(amount_of_coindencess[13], 1440);
    ASSERT_EQ(amount_of_coindencess[14], 3240);

    free(amount_of_coindencess);
    free(sequences);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
