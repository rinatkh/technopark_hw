#pragma once

#include "errors.h"

errors
find_in_file_sequences(const char *filename, const unsigned long file_size,
                       const char **sequences, const int count_of_sequences,
                       int *amount_of_coindencess);

