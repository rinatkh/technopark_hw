#include <stdio.h>
#include <malloc.h>
#include <stddef.h>

#include "console_communication.h"
#include "errors.h"

errors get_file_size(const char *filename, unsigned long *result) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file\n");
        return ERROR_INPUT;
    }
    fseek(file, 0, SEEK_END);
    *result = ftell(file);
    if (fclose(file)) {
        fprintf(stderr, "Failed to close file\n");
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
        printf("Nothing more to read - and no number found\n");
        return ERROR_INPUT;
    }
    return SUCCESS;
}

char **get_sequences(const int count_of_sequences) {
    char **sequences = (char **) malloc(count_of_sequences * sizeof(char *));
    if (sequences == NULL) {
        return NULL;
    }
    for (int i = 0; i < count_of_sequences; i++) {
        sequences[i] = (char *) malloc(sizeof(char) * 10);
        if (sequences[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(sequences[j]);
            }
            free(sequences);
            return NULL;
        }
        int res;
        printf("\nEnter an sequence: ");
        while ((res = scanf("%s", sequences[i])) == 0) {
            scanf("%*[^\n]");
        }
        if (res == EOF) {
            printf("Nothing more to read - and no number found\n");
            for (int j = 0; j <= i; j++) {
                free(sequences[j]);
            }
            free(sequences);
            return NULL;
        }
    }
    return sequences;
}

void free_memmory(char **sequences, const int count_of_sequences, int *amount_of_coindencess) {
    if (sequences != NULL) {
        for (int i = 0; i < count_of_sequences; i++) {
            if (sequences[i] != NULL) {
                free(sequences[i]);
            }
        }
        free(sequences);
    }
    if (amount_of_coindencess != NULL) {
        free(amount_of_coindencess);
    }
}

void print_result(const char **sequences, const int count_of_sequences,
             const int *amount_of_coindencess) {
    printf("\n");
    for (int i = 0; i < count_of_sequences; i++) {
        printf("Количество найденной последовательности \"%s\" : %i\n", sequences[i],
               amount_of_coindencess[i]);
    }
}
