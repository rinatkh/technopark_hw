#pragma once
#include <sys/sysinfo.h>

#define MAX_COUNT_PTHREADS get_nprocs_conf()

typedef struct {
    const char *sequence;
    int amount_sequences;
    const char *filename;
    unsigned long file_size;

} thread_data;

