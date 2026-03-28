#include "../include/chromosome.h"
#include "../include/tsp.h"
#include "../include/population.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int compute_fitness(const uint8_t *cities, const tsp_t *tsp) {
    int sum = 0;
    for (int i = 0; i < tsp->num_of_cities - 1; i++) {
        sum += dist_get(tsp, cities[i], cities[i + 1]);
    }

    sum += dist_get(tsp, cities[tsp->num_of_cities - 1], cities[0]);
    return sum;
}

void shuffle (uint8_t *arr, int num_of_cities) {
    for (int i = num_of_cities - 1; i > 1; i--) {
        uint8_t j = arc4random_uniform(i) + 1;

        uint8_t tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;
    }
}

chromosome_t *chromosome_init_random (const tsp_t *tsp) {
    chromosome_t *chr = malloc(sizeof(chromosome_t));
    chr->cities = malloc(sizeof(uint8_t) * tsp->num_of_cities);
    for (uint8_t i = 0; i < tsp->num_of_cities; i++) {
        chr->cities[i] = i;
    }
    chr->length = tsp->num_of_cities;

    shuffle(chr->cities, tsp->num_of_cities);
    chr->fitness = compute_fitness(chr->cities, tsp);
    return chr;
}

chromosome_t *tournament_select(const population_t *pop) {
    chromosome_t *candidates[pop->tournament_size];
    
    for (int i = 0; i < pop->tournament_size; i++) {
        chromosome_t *candidate;
        bool unique;
        
        do {
            unique = true;
            int idx = arc4random_uniform(pop->size);
            candidate = pop->arr[idx];
            
            for (int j = 0; j < i; j++) {
                if (candidates[j] == candidate) {
                    unique = false;
                    break;
                }
            }
        } while (!unique);
        
        candidates[i] = candidate;
    }
    
    chromosome_t *best = candidates[0];
    for (int i = 1; i < pop->tournament_size; i++) {
        if (candidates[i]->fitness < best->fitness)
            best = candidates[i];
    }
    
    return best;
}


chromosome_t chromosome_crossover (population_t *pop) {
    chromosome_t *parent_a = tournament_select(pop);   
    chromosome_t *parent_b = NULL;
    do {
        chromosome_t *parent_b = tournament_select(pop);
    } while (parent_a == parent_b);

    chromosome_t child;
    return child;
}
/*
void chromosome_mutate (chromosome_t *chromosome, int num_of_cities) {

}
*/

void chromosome_free (chromosome_t *chr) {
    free(chr->cities);
    free(chr);
}

void chromosome_print (const chromosome_t *chr) {
    for (int i = 0; i < chr->length; i++) {
        printf("%d", chr->cities[i]);
    }
    printf("\n");
}
