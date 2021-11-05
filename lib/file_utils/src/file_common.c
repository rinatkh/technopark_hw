#include <stddef.h>
#include <string.h>

#include "file_utils.h"

int find_sequence(const char *sequence, const char *region, const unsigned long file_size) {
    if (sequence == NULL || region == NULL) {
        return -1;
    }
    int amount_of_coindencess = 0;
    unsigned long matches = 0;
    for (unsigned long j = 0; j < file_size; j++) {
        char c = region[j];
        if (c == sequence[matches]) {
            matches++;
        } else {
            matches = 0;
        }
        if (matches == strlen(sequence)) {
            amount_of_coindencess++;
            matches = 0;
        }
    }
    return amount_of_coindencess;
}
