#include "../include/config.h"
#include "../include/tsp.h"
#include "../include/population.h"
#include "../include/log.h"

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

    dist_arr_free(&tsp);
    LOG_OK("TSP free");
    population_free (&pop_curr);
    LOG_OK("Population free");
    LOG_OK("Population 2 free");
    LOG_OK("Program finished!");
    
    return 0;
}
