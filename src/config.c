#include "../include/config.h"
#include "stdio.h"
#include "../include/log.h"

config_t config_default(void) {
    config_t config = {
        .num_of_cities = 10,
        .random = true
    };

    return config;
}

config_t config_parse (int argc, char *argv[]) {
    config_t config;
    if (argc == 1) {
        LOG_INFO("Initializing config with default parameters");
        config = config_default();
    } else {
       printf("Initializing config from given data"); 
    }

    return config;
}


