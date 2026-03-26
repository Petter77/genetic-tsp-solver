#include "../include/chromosome.h"
#include "../include/tsp.h"

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

/*
chromosome_t chromosome_crossover ( const chromosome_t *parent_a, 
                                    const chromosome_t *parent_b,
                                    int num_of_cities) {

}

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
