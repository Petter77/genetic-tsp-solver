# TSP Solver — Genetic Algorithm (C)

A genetic algorithm implementation for solving the **Asymmetric Travelling Salesman Problem (ATSP)** written in C.

## Problem

The Travelling Salesman Problem asks: given a set of cities and distances between them,
what is the shortest route that visits each city exactly once and returns to the origin?
This implementation targets the **asymmetric** variant, where dist(A->B) =/= dist(B->A).

## Algorithm Overview

| Component | Implementation |
|---|---|
| Representation | Permutation chromosome (`uint8_t` array of city indices) |
| Initial population | Random permutations |
| Selection | Tournament selection |
| Crossover | OX1 (Order Crossover) *(in progress)* |
| Mutation | Swap mutation *(in progress)* |
| Local search | 2-opt *(planned)* |
| Fitness | Total route cost (sum of edge weights) |

## Build & Run

**Requirements:** GCC, Make
```bash
make          # build
make re       # rebuild from scratch
make clean    # remove object files
make fclean   # remove entire build directory
```
```bash
./build/program              # run with default config (10 cities, pop. 1000)
./build/program <options>    # run with custom parameters (WIP)
```

> Built with `-fsanitize=address` by default for memory safety during development.

## Configuration (defaults)

| Parameter | Default | Description |
|---|---|---|
| `num_of_cities` | 10 | Number of cities |
| `population_size` | 1000 | Chromosomes per generation |
| `tournament_size` | 3 | Candidates per tournament |
| `random` | true | Generate random distance matrix |

## Project Structure
```
.
├── include/
│   ├── chromosome.h   # Chromosome struct & operations
│   ├── population.h   # Population management
│   ├── tsp.h          # Distance matrix & TSP instance
│   ├── config.h       # CLI config parsing
│   └── log.h          # Logging macros
├── src/
│   ├── chromosome.c   # Crossover, mutation, fitness
│   ├── population.c   # Init, selection, lifecycle
│   ├── tsp.c          # Matrix generation & access
│   ├── config.c       # Argument parsing
│   └── main.c
└── Makefile
```

## Status

**Actively developed**

- [x] Random population initialization
- [x] Tournament selection
- [x] Fitness evaluation
- [ ] OX1 crossover
- [ ] Swap mutation
- [ ] Generational loop
- [ ] 2-opt local search
- [ ] File input (TSPLIB format)
- [ ] Convergence visualization
