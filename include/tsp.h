#ifndef TSP_H
#define TSP_H

#include "config.h"
#include <stdint.h>

typedef struct {
    int num_of_cities;
    int* dist_arr_ptr; 
} tsp_t;

static inline int dist_get(const tsp_t *tsp, int i, int j) {
    return tsp->dist_arr_ptr[i * tsp->num_of_cities + j];
}


int* fill_matrix_random (int num_of_cities);

tsp_t tsp_initialize (const config_t *config);

void dist_print(const tsp_t *tsp);

void dist_arr_free(tsp_t *tsp);

#endif 
