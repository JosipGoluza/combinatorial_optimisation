//
// Created by josip on 12/12/2024.
//

#ifndef EXAMPLE_H
#define EXAMPLE_H
#include <map>
#include <utility>
#include <vector>

#include "Instance.h"
using namespace std;

enum CrossoverType {
    ONE_POINT,
    TWO_POINT
};

static const char * crossoverTypeToString(CrossoverType type) {
    switch (type) {
        case ONE_POINT:
            return "ONE_POINT";
        case TWO_POINT:
            return "TWO_POINT";
        default:
            return "UNKNOWN";
    }
}


struct Examples {
    std::vector<Instance> instance;
    std::map<int, int> solutionMap;

    Examples(std::vector<Instance> inst, const std::map<int, int> &solMap)
        : instance(std::move(inst)), solutionMap(solMap) {
    }
};

struct Algorithm {
    int n;
    InstanceType type;
    Examples exampleList;
    int population_size;
    double mutation_rate;
    double crossover_rate;
    int tournament_size;
    int num_elites;
    CrossoverType crossover_type;
    int num_generations;

    Algorithm(const int n_, const InstanceType t, Examples e, const int pop_size, const double mut_rate, const double cross_rate, const int tour_size, const int elites, const CrossoverType cross_type, const int num_gen)
        : n(n_), type(t), exampleList(std::move(e)), population_size(pop_size), mutation_rate(mut_rate), crossover_rate(cross_rate), tournament_size(tour_size), num_elites(elites), crossover_type(cross_type), num_generations(num_gen) { }
};

#endif //EXAMPLE_H
