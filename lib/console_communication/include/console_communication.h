#pragma once

#include "errors.h"

errors get_file_size(const char *filename, unsigned long *result);

errors count_reading(int *count_of_sequences);

char **get_sequences(const int count_of_sequences);

void free_memmory(char **sequences, const int count_of_sequences, int *amount_of_coindencess);

errors print_result(const char **sequences,const int count_of_sequences,const int *amount_of_coindencess);
