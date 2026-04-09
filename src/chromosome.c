#include "../include/chromosome.h"
#include "../include/tsp.h"
#include "../include/population.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void chromosome_print (const chromosome_t *chr) {
    for (int i = 0; i < chr->length; i++) {
        printf("%d ", chr->cities[i]);
    }
    printf("\n");
}

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
        parent_b = tournament_select(pop);
    } while (parent_a == parent_b);

    printf("Parent A:\n");
    chromosome_print(parent_a);
    printf("Parent B:\n");
    chromosome_print(parent_b);

    uint8_t cut1 = arc4random_uniform(parent_a->length - 2) + 1;
    uint8_t cut2;
    do {
        cut2 = arc4random_uniform(parent_a->length - 2) + 1;
    } while (cut2 == cut1 || abs(cut2 - cut1) < 2);

    if (cut1 > cut2) { uint8_t tmp = cut1; cut1 = cut2; cut2 = tmp; }
    printf("Cut 1: %d\n", cut1);
    printf("Cut 2: %d\n", cut2);

    chromosome_t child;
    child.length = parent_a->length;
    child.cities = malloc(sizeof(uint8_t) * child.length);
    child.fitness = 0;

    for (int i = 0; i < child.length; i++) {
        child.cities[i] = 255;
    }

    for (uint8_t i = cut1; i <= cut2; i++) {
        child.cities[i] = parent_a->cities[i];
    }

    uint8_t missing = (child.length - (cut2 - cut1) - 1);
    uint8_t missing_arr[missing];

    int missing_index = 0;
    for (int i = 0; i < child.length; i++) {
        bool present = false;
        for (int j = 0; j < child.length; j++) {
            if (parent_b->cities[i] == child.cities[j]) {
                present = true;
                break;
            }
        }
        if (!present) { 
            missing_arr[missing_index] = parent_b->cities[i];
            missing_index++;
        }
    }
    for (int j = 0; j < missing; j++) {
        for (int i = 0; i < child.length; i++){
            if (child.cities[i] == 255) {
                child.cities[i] = missing_arr[j];
                break;
            }
        }
    }

    printf("child:\n");
    chromosome_print(&child);
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

