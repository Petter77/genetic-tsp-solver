#include "../include/tsp.h"
#include "stdlib.h"

int* fill_matrix_random (int num_of_cities) {
    int* arr = (int*)malloc(num_of_cities * num_of_cities * sizeof(int));

    for (int i = 0; i < num_of_cities * num_of_cities; i++) {
        arr[i] = i;
    }

    return arr;
}

tsp_t tsp_initialize(config_t config) {
    tsp_t tsp;
    if (config.random) {
        tsp.dist_arr_ptr = fill_matrix_random(config.num_of_cities);
    }


    return tsp;
}
