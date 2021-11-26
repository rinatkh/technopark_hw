#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <stdbool.h>

#include "file_utils.h"

#define MAX_COUNT_PTHREADS get_nprocs_conf()

typedef struct {
    int amount_sequences;
    const char *filename;
    unsigned long file_size;
    char *region;
    char **sequences;
    int *result;
} thread_data;


static void *my_thread(void *thread_input_data) {
    thread_data *data = (thread_data *) thread_input_data;
    data->result = (int *) malloc(data->amount_sequences * sizeof(int));
    for (int i = 0; i < data->amount_sequences; i++) {
        int result = find_sequence(data->sequences[i], data->region, data->file_size);
        if (result == -1) {
            printf("find sequence failed\n");

        } else {
            data->result[i] = result;
        }
    }
    return NULL;
}

static bool isBiggerThanCountOfCores(int count_of_sequences) {
    return count_of_sequences > MAX_COUNT_PTHREADS;
}

static int maxValue(int count_of_sequences) {
    return isBiggerThanCountOfCores(count_of_sequences) ? MAX_COUNT_PTHREADS : count_of_sequences;
}

static errors
splitDataByThreads(thread_data *data, const int count_of_sequences, char **sequences) {
    if (isBiggerThanCountOfCores(count_of_sequences)) {
        int amountOfPeriods = (count_of_sequences / MAX_COUNT_PTHREADS) + 1;
        for (int i = 0; i < MAX_COUNT_PTHREADS; i++) {
            data[i].sequences = (char **) malloc(amountOfPeriods * sizeof(char *));
            if (data[i].sequences == NULL) {
                return ERROR_MEMORY;
            }
            data[i].amount_sequences = 0;
        }

        for (int i = 0; i < count_of_sequences; i++) {
            int i_current = i % MAX_COUNT_PTHREADS;
            int j_current = i / MAX_COUNT_PTHREADS;
            data[i_current].sequences[j_current] = sequences[i];
            data[i].amount_sequences++;
        }
    } else {
        for (int i = 0; i < count_of_sequences; i++) {
            data[i].sequences = (char **) malloc(sizeof(char *));
            if (data[i].sequences == NULL) {
                return ERROR_MEMORY;
            }
            int i_current = i % MAX_COUNT_PTHREADS;
            int j_current = i / MAX_COUNT_PTHREADS;
            data[i_current].sequences[j_current] = sequences[i];
            data[i].amount_sequences = 1;
        }
    }
    return SUCCESS;
}


errors find_in_file_sequences(const char *filename,
                              const unsigned long file_size,
                              const char **sequences,
                              const int count_of_sequences,
                              int *amount_of_coindencess) {
    if (filename == NULL || sequences == NULL || amount_of_coindencess == NULL) {
        return ERROR_NULL_ARGS;
    }

    pthread_t *threads = (pthread_t *) malloc(maxValue(count_of_sequences) * sizeof(pthread_t));
    if (threads == NULL) {
        return ERROR_MEMORY;
    }


    thread_data *data = (thread_data *) malloc(
            maxValue(count_of_sequences) * sizeof(thread_data));
    if (data == NULL) {
        free(threads);
        return ERROR_MEMORY;
    }

    int res = 0;
    if ((res = splitDataByThreads(data, count_of_sequences, (char **) sequences)) != SUCCESS) {
        return res;
    }


    int fd = open(filename, O_RDWR);
    char *region = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (region == MAP_FAILED) {
        printf("mmap failed\n");
        close(fd);
        free(threads);
        free(data);
        return ERROR_FILE;
    }

    for (int j = 0; j < maxValue(count_of_sequences); j++) {
        data[j].result = 0;
        data[j].filename = filename;
        data[j].file_size = file_size;
        data[j].region = region;

        if (pthread_create(&(threads[j]), NULL, my_thread, &data[j]) != 0) {
            free(threads);
            free(data);
            close(fd);
            munmap(region, file_size);
            return ERROR_PHTREAD;
        }
    }

    for (int i = 0; i < count_of_sequences; i++) {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < count_of_sequences; i++) {
        int i_current = i % MAX_COUNT_PTHREADS;
        int j_current = i / MAX_COUNT_PTHREADS;
        amount_of_coindencess[i] = data[i_current].result[j_current];
    }
    for (int i = 0; i < maxValue(count_of_sequences); i++) {
        free(data[i].result);
        free(data[i].sequences);
    }

    free(threads);
    free(data);

    if (munmap(region, file_size) != 0) {
        close(fd);
        return ERROR_FILE;
    }
    close(fd);

    return SUCCESS;
}
