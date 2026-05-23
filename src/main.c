#include "../include/config.h"
#include "../include/tsp.h"
#include "../include/population.h"
#include "../include/log.h"
#include "../include/chromosome.h"
#include <string.h>

static int brute_force_fitness;
static uint8_t brute_force_best[10];

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
    for (int i = 0; i < tsp->num_of_cities; i++) cities[i] = i;

    brute_force_fitness = 999999999;
    permute(cities, 1, tsp->num_of_cities, tsp);  // start od 1 — miasto 0 ustalone

    LOG_INFO("Brute force best fitness: %d", brute_force_fitness);
}

int main (int argc, char *argv[]) {
    config_t config = config_parse(argc, argv);
    tsp_t tsp = tsp_initialize(&config);

    population_t pop_curr = population_init (&config, &tsp);

    for (int i = 0; i < config.generations; i++) {
        population_t pop_next = population_new(&tsp, &pop_curr);
        LOG_INFO("New population created");
        population_free(&pop_curr);
        LOG_INFO("Old population erased");
        pop_curr = pop_next;
        LOG_INFO("Generation %d, best fitness: %d", i, best_fitness(&pop_curr)->fitness);
    }

    brute_force(&tsp);

    dist_arr_free(&tsp);
    LOG_OK("TSP free");
    population_free (&pop_curr);
    LOG_OK("Population free");
    LOG_OK("Population 2 free");
    LOG_OK("Program finished!");
    
    return 0;
}
