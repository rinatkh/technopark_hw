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
    char *region;
} thread_data;

static sem_t semaphore;

static void *my_thread(void *thread_input_data) {
    sem_wait(&semaphore);
    thread_data *data = (thread_data *) thread_input_data;
    int fd = open(data->filename, O_RDWR);

    int result = find_sequence(data->sequence, data->region, data->file_size);
    if (result == -1) {
        printf("find sequence failed\n");
        close(fd);
        exit(-1);
    } else {
        data->amount_sequences = result;
    }

    sem_post(&semaphore);
    return NULL;
}

errors find_in_file_sequences(const char *filename,
                              const unsigned long file_size,
                              const char **sequences,
                              const int count_of_sequences,
                              int *amount_of_coindencess) {
    if (filename == NULL || sequences == NULL || amount_of_coindencess == NULL) {
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

    int fd = open(filename, O_RDWR);
    char *region = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (region == MAP_FAILED) {
        printf("mmap failed\n");
        close(fd);
        free(threads);
        free(data);
        return ERROR_FILE;
    }

    for (int j = 0; j < count_of_sequences; j++) {
        data[j].sequence = sequences[j];
        data[j].amount_sequences = 0;
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

    for (int j = 0; j < count_of_sequences; j++) {
        pthread_join(threads[j], NULL);
    }
    for (int j = 0; j < count_of_sequences; j++) {
        amount_of_coindencess[j] = data[j].amount_sequences;
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








