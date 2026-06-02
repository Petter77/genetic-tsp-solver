#include "../include/population.h"
#include "../include/tsp.h"
#include "../include/chromosome.h"
#include <stdlib.h>
#include <string.h>



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

population_t population_new(const tsp_t *tsp, population_t *pop, int mutation_rate) {
    population_t population = {
        .size = pop->size,
        .tournament_size = pop->tournament_size,
        .arr = malloc(sizeof(chromosome_t*) * pop->size)
    };

    chromosome_t *elite = best_fitness(pop);
    population.arr[0] = chromosome_copy(elite);
    two_opt(population.arr[0], tsp);

    for (int i = 1; i < population.size; i++) {
        population.arr[i] = chromosome_crossover(pop, tsp);
        if ((int)arc4random_uniform(100) < mutation_rate)
            chromosome_mutate(population.arr[i], tsp);
    }

    return population;
}
chromosome_t *chromosome_copy(const chromosome_t *src) {
    chromosome_t *copy = malloc(sizeof(chromosome_t));
    copy->length = src->length;
    copy->fitness = src->fitness;
    copy->cities = malloc(sizeof(uint8_t) * src->length);
    memcpy(copy->cities, src->cities, src->length);
    return copy;
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

chromosome_t *best_fitness(const population_t *pop) {
    chromosome_t *best = pop->arr[0];
    for (int i = 1; i < pop->size; i++) {
        if (pop->arr[i]->fitness < best->fitness)
            best = pop->arr[i];
    }

    return best;
}
