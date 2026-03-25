#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "tsp.h"

#include <stdint.h>

typedef struct {
    uint8_t *cities;
    int fitness;
} chromosome_t;


chromosome_t chromosome_init_random (const tsp_t *tsp);

chromosome_t chromosome_crossover ( const chromosome_t *parent_a, 
                                    const chromosome_t *parent_b,
                                    int num_of_cities);

void chromosome_mutate (chromosome_t *chromosome, int num_of_cities);
void chromosome_free (chromosome_t chr);

#endif
