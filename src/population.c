#include "../include/population.h"
#include "../include/tsp.h"
#include "../include/chromosome.h"
#include <stdlib.h>


population_t population_init (const config_t *config, const tsp_t *tsp) {
     population_t population = {
        .size = config->population_size,
        .tournament_size = config->tournament_size,
        .arr = malloc(sizeof(chromosome_t*) * config->population_size)
    };
   
    for (int i = 0; i < population.size; i++) {
        population.arr[i] = chromosome_init_random(tsp);
    }
    return population;
   
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

