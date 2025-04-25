//
// Created by josip on 17/12/2024.
//

#include "calculate_genetic.h"

int calculate_genetic_algorithm(KnapsackGA & generic_algorithm) {
    generic_algorithm.evolve();

    return generic_algorithm.getBestSolution().fitness;
}
