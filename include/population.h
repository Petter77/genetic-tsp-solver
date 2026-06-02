#ifndef POPULATION_H
#define POPULATION_H

#include "chromosome.h"
#include "config.h"

typedef struct population_s {
    int size;
    int tournament_size;
    chromosome_t **arr;
} population_t;

void population_free(population_t *pop);
void population_print(const population_t *pop);
population_t population_init(const config_t *config, const tsp_t *tsp);
population_t population_new(const tsp_t *tsp, population_t *pop, int mutation_rate);
chromosome_t *best_fitness(const population_t *pop);
chromosome_t *chromosome_copy(const chromosome_t *src);

#endif
