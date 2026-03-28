#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "tsp.h"
#include <stdint.h>

typedef struct population_s population_t;

typedef struct {
    uint8_t *cities;
    int fitness;
    uint8_t length;
} chromosome_t;


chromosome_t *chromosome_init_random (const tsp_t *tsp);

chromosome_t chromosome_crossover (population_t *pop);

void chromosome_mutate (chromosome_t *chromosome, int num_of_cities);
void chromosome_free (chromosome_t *chr);

void chromosome_print (const chromosome_t *chr);
#endif
