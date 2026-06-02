#include "../include/config.h"
#include "../include/tsp.h"
#include "../include/population.h"
#include "../include/log.h"
#include "../include/chromosome.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>

static int brute_force_fitness;
static uint8_t *brute_force_best;

void permute(uint8_t *cities, int start, int n, const tsp_t *tsp) {
    if (start == n) {
        int fit = compute_fitness(cities, tsp);
        if (fit < brute_force_fitness) {
            brute_force_fitness = fit;
            memcpy(brute_force_best, cities, n);
        }
        return;
    }
    for (int i = start; i < n; i++) {
        uint8_t tmp = cities[start]; cities[start] = cities[i]; cities[i] = tmp;
        permute(cities, start + 1, n, tsp);
        tmp = cities[start]; cities[start] = cities[i]; cities[i] = tmp;
    }
}

void brute_force(const tsp_t *tsp) {
    uint8_t cities[tsp->num_of_cities];
    brute_force_best = malloc(sizeof(uint8_t) * tsp->num_of_cities);

    for (int i = 0; i < tsp->num_of_cities; i++) cities[i] = i;

    brute_force_fitness = INT_MAX;
    permute(cities, 1, tsp->num_of_cities, tsp);

    LOG_INFO("Brute force best fitness: %d", brute_force_fitness);
    free(brute_force_best);
}

int main(int argc, char *argv[]) {
    config_t config = config_parse(argc, argv);
    tsp_t tsp = tsp_initialize(&config);

    population_t pop_curr = population_init(&config, &tsp);

    int stagnation   = 0;
    int mutation_rate = 5;
    int best_so_far  = best_fitness(&pop_curr)->fitness;

    for (int i = 0; i < config.generations; i++) {
        population_t pop_next = population_new(&tsp, &pop_curr, mutation_rate);
        population_free(&pop_curr);
        pop_curr = pop_next;

        int current_best = best_fitness(&pop_curr)->fitness;
        LOG_INFO("Generation %d | best: %d | mutation_rate: %d%%",
                 i, current_best, mutation_rate);

        if (current_best < best_so_far) {
            best_so_far   = current_best;
            stagnation    = 0;
            mutation_rate = 5;
        } else {
            stagnation++;
            if (stagnation > 20 && mutation_rate < 50)
                mutation_rate += 2;
        }
    }

    LOG_OK("GA best fitness: %d", best_so_far);
    //brute_force(&tsp);

    dist_arr_free(&tsp);
    population_free(&pop_curr);
    LOG_OK("Program finished!");

    return 0;
}
