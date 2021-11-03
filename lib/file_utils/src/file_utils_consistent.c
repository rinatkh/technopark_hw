#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "file_utils.h"

static void
find_sequences(const char **sequences, const int count_of_sequences,
               int *amount_of_coindencess, const char *region,
               const unsigned long file_size) {
    for (int i = 0; i < count_of_sequences; i++) {
        char c = '\0';
        unsigned long matches = 0;
        const char *current_sequence = sequences[i];
        for (unsigned long j = 0; j < file_size; j++) {
            c = region[j];
            if (c == current_sequence[matches]) matches++;
            else matches = 0;

            if (matches == strlen(current_sequence)) {
                amount_of_coindencess[i]++;
                matches = 0;
            }
        }
    }
}

errors
find_in_file_sequences(const char *filename, const unsigned long file_size,
                       const char **sequences, const int count_of_sequences,
                       int *amount_of_coindencess) {

    int fd = open(filename, O_RDWR);
    char *region = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);
    if (region == MAP_FAILED) {
        printf("mmap failed\n");
        close(fd);
        return ERROR_MEMORY;
    }
    find_sequences(sequences, count_of_sequences, amount_of_coindencess, region, file_size);
    if (munmap(region, file_size) != 0) {
        printf("munmap failed\n");
        return ERROR_MEMORY;
    }
    close(fd);
    return SUCCESS;
}


