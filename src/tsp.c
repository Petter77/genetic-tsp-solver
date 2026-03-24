#include "../include/tsp.h"
#include "../include/log.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int *fill_matrix_random(int n) {
    int size = n * (n - 1) / 2;
    int *arr = malloc(size * sizeof(int));

    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100 + 1;
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

static inline int dist_get(const tsp_t *tsp, int i, int j) {
    if (i == j) {
        return 0;
    }

    if (i < j) { 
        int tmp = i; 
        i = j; 
        j = tmp; 
    }

    return tsp->dist_arr_ptr[i * (i - 1) / 2 + j];
}

tsp_t tsp_initialize(const config_t config) {
    tsp_t tsp;
    tsp.num_of_cities = config.num_of_cities;
    if (config.random) {
        tsp.dist_arr_ptr = fill_matrix_random(config.num_of_cities);
    }

    return tsp;
}
