#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>

int time_control(int *amounts_of_coincidence_from_lib, int amount_of_sequences, const char *lib_run) {
    if (system(lib_run)) {
        return -1;
    }

    int fd_res = open("result.txt", O_RDWR);
    if (fd_res < 0) {
        return -1;
    }

    unsigned int i = read(fd_res, amounts_of_coincidence_from_lib, (amount_of_sequences + 1) * sizeof(int));
    if (i != (amount_of_sequences + 1) * sizeof(int)) {
        close(fd_res);
        return -1;
    }

    close(fd_res);
    return 0;
}

int get_result_lib(int *amounts_of_coincidence_from_lib, int amount_of_sequences, const char *lib_run) {
    int lib_time = 0;
    for (int i = 0; i < 5; i++) {
        if (time_control(amounts_of_coincidence_from_lib, amount_of_sequences, lib_run)) {
            return -1;
        }
        lib_time += amounts_of_coincidence_from_lib[amount_of_sequences];
    }

    lib_time /= 5;
    return lib_time;
}

int main() {
    int amount_of_sequences = 3;
    int *amounts_of_coincidence_from_static = malloc((amount_of_sequences + 1) * sizeof(int));
    if (amounts_of_coincidence_from_static == NULL) {
        return -1;
    }
    int *amounts_of_coincidence_from_dynamic = malloc((amount_of_sequences + 1) * sizeof(int));
    if (amounts_of_coincidence_from_dynamic == NULL) {
        free(amounts_of_coincidence_from_static);
        return -1;
    }

    int time_static_lib = get_result_lib(amounts_of_coincidence_from_static, amount_of_sequences,
                                         "../test/stress_test_s ../../../files/100mb.txt 3 announced disapperared discreetly");
    if (time_static_lib == -1) {
        free(amounts_of_coincidence_from_dynamic);
        free(amounts_of_coincidence_from_static);
        return -1;
    }

    int time_dynamic_lib = get_result_lib(amounts_of_coincidence_from_dynamic, amount_of_sequences,
                                          "../test/stress_test_d ../../../files/100mb.txt 3 announced disapperared discreetly");
    if (time_dynamic_lib == -1) {
        free(amounts_of_coincidence_from_dynamic);
        free(amounts_of_coincidence_from_static);
        return -1;
    }

    for (int i = 0; i < amount_of_sequences; ++i) {
        if (amounts_of_coincidence_from_dynamic[i] != amounts_of_coincidence_from_static[i]) {
            free(amounts_of_coincidence_from_static);
            free(amounts_of_coincidence_from_dynamic);
            return -1;
        }
    }

    printf("static lib time: %i; dynamic lib time: %i\n", time_static_lib, time_dynamic_lib);
    free(amounts_of_coincidence_from_dynamic);
    free(amounts_of_coincidence_from_static);
    return 0;
}


