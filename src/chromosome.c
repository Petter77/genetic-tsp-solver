#include "../include/chromosome.h"
#include "../include/tsp.h"

#include <stdint.h>
#include <stdlib.h>

int compute_fitness(const uint8_t *cities, int num_of_cities, const tsp_t *tsp) {
    int sum = 0;
    for (int i = 0; i < num_of_cities - 1; i++) {
        sum += dist_get(tsp, cities[i], cities[i + 1]);
    }

    sum += dist_get(tsp, cities[num_of_cities - 1], cities[0]);
    return sum;
}

void shuffle (uint8_t *arr, int num_of_cities) {
    for (int i = num_of_cities - 1; i > 0; i--) {
        uint8_t j = arc4random_uniform(i+1);

        uint8_t tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;
    }
}

chromosome_t chromosome_init_random (const tsp_t *tsp, int num_of_cities) {
    chromosome_t chromosome;
    chromosome.cities = malloc(sizeof(uint8_t) * num_of_cities);
    for (uint8_t i = 0; i < num_of_cities; i++) {
        chromosome.cities[i] = i;
    }
    shuffle(chromosome.cities, num_of_cities);

    return chromosome;
}

/*
chromosome_t chromosome_crossover ( const chromosome_t *parent_a, 
                                    const chromosome_t *parent_b,
                                    int num_of_cities) {

}

void chromosome_mutate (chromosome_t *chromosome, int num_of_cities) {

}
*/

void chromosome_free (chromosome_t chr) {
    free(chr.cities);
}
