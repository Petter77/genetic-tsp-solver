#include "../include/population.h"
#include "../include/tsp.h"
#include "../include/chromosome.h"
#include <stdlib.h>

population_t first_population (const config_t *config) {
    population_t population = {
        .size = config->population_size,
        .tournament_size = config->tournament_size,
        .arr = malloc(sizeof(chromosome_t*) * config->population_size)
    };
   
    return population;
}

void population_fill (const tsp_t *tsp, population_t *pop) {
    for (int i = 0; i < pop->size; i++) {
        pop->arr[i] = chromosome_init_random(tsp);
    }
}

void population_free (population_t *pop) {
    for (int i = 0; i < pop->size; i++) {
        chromosome_free (pop->arr[i]);
    }
    free(pop->arr);
}

void population_print (const population_t *pop) {
    for (int i = 0; i < pop->size; i++) {
        chromosome_print(pop->arr[i]);
    }
}

