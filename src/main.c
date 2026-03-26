#include "../include/config.h"
#include "../include/tsp.h"
#include "../include/population.h"

int main (int argc, char *argv[]) {
    config_t config = config_parse(argc, argv);
    tsp_t tsp = tsp_initialize(&config);

    population_t population = population_init (&config, &tsp);
    population_print(&population);

    dist_arr_free(&tsp);
    population_free (&population);
    return 0;
}
