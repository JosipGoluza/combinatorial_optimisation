//
// Created by josip on 06/01/2025.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <vector>

#include "Instance.h"

enum ParameterChange {
    NONE,
    POPULATION_SIZE,
    TOURNAMENT_SIZE,
    NUM_ELITES,
    NUM_GENERATIONS,
    MAX_ATTEMPTS,
    MUTATION_RATE,
    CROSSOVER_RATE,
    CHANGE_THRESHOLD,
};

inline string parameterChangeToFolder(const ParameterChange parameter_changed) {
    switch (parameter_changed) {
        case NONE:
            return "none";
        case POPULATION_SIZE:
            return "population";
        case TOURNAMENT_SIZE:
            return "tournament";
        case NUM_ELITES:
            return "elites";
        case NUM_GENERATIONS:
            return "generations";
        case MAX_ATTEMPTS:
            return "attempts";
        case MUTATION_RATE:
            return "mutation";
        case CROSSOVER_RATE:
            return "crossover";
        case CHANGE_THRESHOLD:
            return "threshold";
    }
    return "none";
}

struct Algorithm {
    int variable_number;
    int clauses_number;
    std::vector<Example> exampleList;
    InstanceType instance_type;
    int population_size; // not clear, should be tested
    int tournament_size; // not clear, should be tested
    int num_elites; // not clear, should be tested
    int num_generations; // not clear, should be tested
    ParameterChange parameter_changed;
    int max_attempts;
    double mutation_rate;
    double crossover_rate;
    double change_threshold;
};

#endif //ALGORITHM_H
