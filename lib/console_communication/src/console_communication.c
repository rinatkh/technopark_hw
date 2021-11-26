#include <stdio.h>
#include <malloc.h>
#include <stddef.h>

#include "console_communication.h"
#include "errors.h"

errors get_file_size(const char *filename, unsigned long *result) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return ERROR_NULL_ARGS;
    }
    fseek(file, 0, SEEK_END);
    if ((*result = ftell(file)) == (long unsigned int) -1) {
        return ERROR_FILE;
    }
    if (fclose(file)) {
        return ERROR_FILE;
    }
    return SUCCESS;
}

errors count_reading(int *count_of_sequences) {
    int res = 0;
    printf("\nEnter a POSITIVE INTEGER number of sequences: ");
    while (((res = scanf("%i", count_of_sequences)) == 0) ||
           (*count_of_sequences < 0)) {
        scanf("%*[^\n]");
        printf("\nEnter a POSITIVE INTEGER number of sequences: ");
    }
    if (res == EOF) {
        return ERROR_NULL_ARGS;
    }
    return SUCCESS;
}

char **get_sequences(const int count_of_sequences) {
    char **sequences = (char **) malloc(count_of_sequences * sizeof(char *));
    if (sequences == NULL) {
        return NULL;
    }
    for (int i = 0; i < count_of_sequences; i++) {

        int res;
        printf("\nEnter an sequence: ");
        while (0 == (res = scanf("%10s", sequences[i]))) {
            scanf("%*[^\n]");
        }
        if (res == EOF) {
            free(sequences);
            return NULL;
        }
    }
    return sequences;
}


errors print_result(const char **sequences, const int count_of_sequences,
                    const int *amount_of_coindencess) {
    if (sequences == NULL || amount_of_coindencess == NULL) {
        return ERROR_NULL_ARGS;
    }
    printf("\n");
    for (int i = 0; i < count_of_sequences; i++) {
        printf("Amount of finded sequence \"%s\" is %i\n", sequences[i],
               amount_of_coindencess[i]);
    }
    return SUCCESS;
}
