#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

typedef struct {
    bool random;
    int num_of_cities;
    int population_size;
    int tournament_size;

} config_t;

config_t config_parse (int argc, char *argv[]);

#endif
