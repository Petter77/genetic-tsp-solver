#include "../include/tsp.h"
#include "../include/log.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

void dist_arr_free(tsp_t *tsp) {
    free(tsp->dist_arr_ptr);
    tsp->dist_arr_ptr = NULL;
}

int *fill_matrix_random(int n) {
    int *arr = malloc(n * n * sizeof(int));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                arr[i * n + j] = 0;
            else
                arr[i * n + j] = rand() % 100 + 1;
        }
    }

    return arr;
}

void dist_print(const tsp_t *tsp) {
    LOG_INFO("print distances matrix");
    int n = tsp->num_of_cities;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", dist_get(tsp, i, j));
        }
        printf("\n");
    }
}

tsp_t tsp_initialize(const config_t* config) {
    tsp_t tsp;
    tsp.num_of_cities = config->num_of_cities;
    if (config->random) {
        tsp.dist_arr_ptr = fill_matrix_random(config->num_of_cities);
    }

    return tsp;
}
