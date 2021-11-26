#pragma once

#include "errors.h"

int find_sequence(const char *sequence, const char *region, const unsigned long file_size);

errors
find_in_file_sequences(const char *filename, const unsigned long file_size,
                       const char **sequences, const int count_of_sequences,
                       int *amount_of_coindencess);

