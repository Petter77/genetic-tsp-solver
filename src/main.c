#include "../include/config.h"
#include "../include/tsp.h"
#include "../include/population.h"
#include "../include/log.h"

#include <stdlib.h>

int main (int argc, char *argv[]) {
    config_t config = config_parse(argc, argv);
    tsp_t tsp = tsp_initialize(&config);

    population_t population = population_init (&config, &tsp);
    //population_print(&population);



    chromosome_t child = chromosome_crossover(&population);
    chromosome_t *child1 = malloc(sizeof(chromosome_t));
    *child1 = child;

    dist_arr_free(&tsp);
    chromosome_free(child1);
    population_free (&population);
    LOG_OK("Program finished!");
    
    return 0;
}
