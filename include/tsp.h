#ifndef TSP_H
#define TSP_H

#include "config.h"

typedef struct {
    int num_of_cities;
    int* dist_arr_ptr; 
} tsp_t;

int* fill_matrix_random (int num_of_cities);

tsp_t tsp_initialize (config_t config);

#endif 
