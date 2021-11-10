#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#include "file_utils.h"

errors
find_in_file_sequences(const char *filename, const unsigned long file_size,
                       const char **sequences, const int count_of_sequences,
                       int *amount_of_coindencess) {
    if (filename == NULL || sequences == NULL || amount_of_coindencess == NULL) {
        return ERROR_NULL_ARGS;
    }

    int fd = open(filename, O_RDWR);
    char *region = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (region == MAP_FAILED) {
        close(fd);
        return ERROR_FILE;
    }
    for (int i = 0; i < count_of_sequences; i++) {
        int result = find_sequence(sequences[i], region, file_size);
        if (result == -1) {
            close(fd);
            return ERROR_NULL_ARGS;
        } else {
            amount_of_coindencess[i] = result;
        }
    }
    if (munmap(region, file_size) != 0) {
        return ERROR_FILE;
    }
    close(fd);
    return SUCCESS;
}
