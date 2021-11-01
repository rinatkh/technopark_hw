#pragma once
#include "errors.h"

errors get_file_size(const char *filename, unsigned long *result);

errors count_reading(int *count_of_sequences);

char **get_sequences(const int count_of_sequences);

void print_sequences(char **sequences, const int count_of_sequences);

