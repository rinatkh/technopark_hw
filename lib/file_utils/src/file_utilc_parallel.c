#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>

#include "file_utils.h"
#include "file_utils_parallel.h"

sem_t semaphore;

static int find_sequences(const char *sequence, const char *region, const unsigned long file_size) {
    int amount_of_coindencess = 0;
    char c = '\0';
    unsigned long matches = 0;
    for (unsigned long j = 0; j < file_size; j++) {
        c = region[j];
        if (c == sequence[matches]) matches++;
        else matches = 0;

        if (matches == strlen(sequence)) {
            amount_of_coindencess++;
            matches = 0;
        }
    }
    return amount_of_coindencess;
}

static int is_bigger_than_max_count_CPU(int count_of_sequences) {
    return (count_of_sequences > MAX_COUNT_PTHREADS ? MAX_COUNT_PTHREADS : count_of_sequences);
}


static void *my_thread(void *thread_D) {
    sem_wait(&semaphore);
    thread_data *data = (thread_data *) thread_D;
    int fd = open(data->filename, O_RDWR);
    char *region = mmap(NULL, data->file_size, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);
    if (region == MAP_FAILED) {
        printf("mmap failed\n");
        close(fd);
        exit(-1);
    }
    data->amount_sequences = find_sequences(data->sequence, region, data->file_size);
    if (munmap(region, data->file_size) != 0) {
        printf("munmap failed\n");
        exit(-1);
    }
    close(fd);
    sem_post(&semaphore);
    return NULL;
}

errors find_in_file_sequences(const char *filename,
                              const unsigned long file_size,
                              const char **sequences,
                              const int count_of_sequences,
                              int *amount_of_coindencess) {
    pthread_t *threads = (pthread_t *) malloc(is_bigger_than_max_count_CPU(count_of_sequences) *
                                              sizeof(pthread_t));
    if (threads == NULL) {
        return ERROR_MEMORY;
    }

    thread_data *thread_D = (thread_data *) malloc(
            is_bigger_than_max_count_CPU(count_of_sequences) * sizeof(thread_data));
    if (thread_D == NULL) {
        free(threads);
        return ERROR_MEMORY;
    }
    sem_init(&semaphore, 0, MAX_COUNT_PTHREADS);
    for (int j = 0; j < is_bigger_than_max_count_CPU(count_of_sequences); j++) {
        thread_D[j].sequence = sequences[j];
        thread_D[j].amount_sequences = 0;
        thread_D[j].filename = filename;
        thread_D[j].file_size = file_size;
        if (!pthread_create(&(threads[j]), NULL, my_thread, &thread_D[j])) {
            free(threads);
            free(thread_D);
            return ERROR_PHTREAD;
        }
    }
    for (int j = 0; j < is_bigger_than_max_count_CPU(count_of_sequences); j++)
        pthread_join(threads[j], NULL);
    for (int j = 0; j < is_bigger_than_max_count_CPU(count_of_sequences); j++)
        amount_of_coindencess[j] = thread_D[j].amount_sequences;

    free(threads);
    free(thread_D);
    return SUCCESS;
}








