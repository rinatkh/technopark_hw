#include <stdio.h>
#include <stddef.h>
#include <malloc.h>

#include "console_communication.h"
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
    char **sequences = NULL;
    if ((sequences = get_sequences(count_of_sequences)) == NULL) {
        fprintf(stderr, "Failed to input sequenses\n");
        return -1;
    }

    int *amount_of_coindencess = (int *) malloc(
            count_of_sequences * sizeof(int));

    if (find_in_file_sequences(argv[1], file_size, (const char **) sequences,
                               count_of_sequences, amount_of_coindencess) != 0) {
        free_memmory(sequences, count_of_sequences, amount_of_coindencess);
        fprintf(stderr, "Failed find any sequences\n");
        return -1;
    }
    print_result((const char **) sequences, count_of_sequences, amount_of_coindencess);
    free_memmory(sequences, count_of_sequences, amount_of_coindencess);
    return 0;
}


