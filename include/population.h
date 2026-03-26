#ifndef POPULATION_H
#define POPULATION_H

#include "chromosome.h"
#include "config.h"

typedef struct {
    int size;
    int tournament_size;
    chromosome_t **arr;
} population_t;


void population_fill (const tsp_t *tsp, population_t *pop);
population_t first_population (const config_t *config);
void population_free (population_t *pop);
void population_print (const population_t *pop);
population_t population_init (const config_t *config, const tsp_t *tsp);

#endif
