// "Copyright 2021 <RINAT>"
#include <stdio.h>

#include "file_utils.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: <file_path>\n");
        return -1;
    }
    unsigned long file_size = 0;
    if ((get_file_size(argv[1], &file_size) != 0)) {
        fprintf(stderr, "Failed to open file or this file doesn't exist\n");
        return -1;
    }
    int count_of_sequences = 0;
    if (count_reading(&count_of_sequences) != 0) {
        fprintf(stderr, "Failed to input the value\n");
        return -1;
    }
    char **sequences = get_sequences(count_of_sequences);

    print_sequences(sequences, count_of_sequences);

    return 0;
}


