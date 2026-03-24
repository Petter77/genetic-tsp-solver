#ifndef TSP_H
#define TSP_H

#include "config.h"

typedef struct {
    int num_of_cities;
    int* dist_arr_ptr; 
} tsp_t;

static inline int dist_get(const tsp_t *tsp, int i, int j);

int* fill_matrix_random (int num_of_cities);

tsp_t tsp_initialize (config_t config);

void dist_print(const tsp_t *tsp);

#endif 
