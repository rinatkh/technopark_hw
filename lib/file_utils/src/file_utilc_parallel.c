#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <stddef.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/sysinfo.h>

#include "file_utils.h"

#define MAX_COUNT_PTHREADS get_nprocs_conf()

typedef struct {
    const char *sequence;
    int amount_sequences;
    const char *filename;
    unsigned long file_size;

} thread_data;

static sem_t semaphore;

static int find_sequence(const char *sequence, const char *region, const unsigned long file_size) {
    int amount_of_coindencess = 0;
    char c = '\0';
    unsigned long matches = 0;
    for (unsigned long j = 0; j < file_size; j++) {
        c = region[j];
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


static void *my_thread(void *thread_input_data) {
    sem_wait(&semaphore);
    thread_data *data = (thread_data *) thread_input_data;
    int fd = open(data->filename, O_RDWR);
    char *region = mmap(NULL, data->file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (region == MAP_FAILED) {
        printf("mmap failed\n");
        close(fd);
        exit(-1);
    }
    data->amount_sequences = find_sequence(data->sequence, region, data->file_size);
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
    if (filename == NULL || sequences == NULL) {
        return ERROR_INPUT;
    }
    pthread_t *threads = (pthread_t *) malloc(count_of_sequences * sizeof(pthread_t));
    if (threads == NULL) {
        return ERROR_MEMORY;
    }

    thread_data *data = (thread_data *) malloc(count_of_sequences * sizeof(thread_data));
    if (data == NULL) {
        free(threads);
        return ERROR_MEMORY;
    }
    sem_init(&semaphore, 0, MAX_COUNT_PTHREADS);
    for (int j = 0; j < count_of_sequences; j++) {
        data[j].sequence = sequences[j];
        data[j].amount_sequences = 0;
        data[j].filename = filename;
        data[j].file_size = file_size;
        if (pthread_create(&(threads[j]), NULL, my_thread, &data[j])) {
            free(threads);
            free(data);
            return ERROR_PHTREAD;
        }
    }
    for (int j = 0; j < count_of_sequences; j++)
        pthread_join(threads[j], NULL);
    for (int j = 0; j < count_of_sequences; j++)
        amount_of_coindencess[j] = data[j].amount_sequences;

    free(threads);
    free(data);
    return SUCCESS;
}








