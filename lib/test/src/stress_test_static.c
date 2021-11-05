#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>

#include "file_utils.h"
#include "console_communication.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: <file_path> <count_of_sequences> <sequence1 sequence2 ..>\n");
        return -1;
    }

    const char *filename = argv[1];
    int count_of_sequences = atoi(argv[2]);

    if (argc != (3 + count_of_sequences)) {
        fprintf(stderr,
                "Usage: <file_path> <count_of_sequences> <sequence1 sequence2 ..>\nEnter correct amount of sequences\n");
        return -1;
    }
    int start = clock();

    unsigned long file_size = 0;
    if ((get_file_size(filename, &file_size) != 0)) {
        fprintf(stderr, "Failed to open file or this file doesn't exist\n");
        return -1;
    }

    char **sequences = (char **) malloc(count_of_sequences * sizeof(char *));
    if (sequences == NULL) {
        fprintf(stderr, "Failed to allocate\n");
        return -1;
    }
    for (int i = 0; i < count_of_sequences; i++) {
        sequences[i] = argv[3 + i];
    }

    int *amount_of_coindencess = (int *) malloc((count_of_sequences + 1) * sizeof(int));
    if (amount_of_coindencess == NULL) {
        free(sequences);
        free(amount_of_coindencess);
        fprintf(stderr, "Failed to allocate\n");
        return -1;
    }

    if (find_in_file_sequences(argv[1], file_size, (const char **) sequences, count_of_sequences,
                               amount_of_coindencess) != 0) {
        free(sequences);
        free(amount_of_coindencess);
        fprintf(stderr, "Failed find any sequences\n");
        return -1;
    }
    int end = clock();
    int result = end - start;
    amount_of_coindencess[count_of_sequences] = result;

    FILE *fd_res = fopen("result.txt", "wb");
    if (!fd_res) {
        free(sequences);
        free(amount_of_coindencess);
        fprintf(stderr, "Failed find output file \"result\"\n");
        return -1;
    }

    if (fwrite(amount_of_coindencess, (count_of_sequences + 1) * sizeof(int), 1, fd_res) != 1) {
        fprintf(stderr, "Failed to write struct into file\n");
        free(sequences);
        free(amount_of_coindencess);
        return -1;
    }

    if (fclose(fd_res)) {
        fprintf(stderr, "Failed to close file\n");
        free(sequences);
        free(amount_of_coindencess);
        return -1;
    }

    free(sequences);
    free(amount_of_coindencess);
    return 0;
}
