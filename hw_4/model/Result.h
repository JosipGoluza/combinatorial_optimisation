//
// Created by josip on 12/12/2024.
//

#ifndef RESULT_H
#define RESULT_H
#include "Instance.h"

struct Result {
    int n;
    InstanceType type;
    long long measuredTime;

    Result(const int n_, const InstanceType t, const long long mt)
        : n(n_), type(t), measuredTime(mt) {}
};

struct ResultGeneticAlgorithm : Result {
    long double average_error;
    int population_size;
    double mutation_rate;
    double crossover_rate;
    int tournament_size;
    int num_elites;
    CrossoverType crossover_type;
    int num_generations;

    ResultGeneticAlgorithm(const int n_, const InstanceType t, const long long mt, const long double ar, const int pop_size, const double mut_rate, const double cross_rate, const int tour_size, const int elites, const CrossoverType cross_type, const int num_gen)
        : Result(n_, t, mt), average_error(ar), population_size(pop_size), mutation_rate(mut_rate), crossover_rate(cross_rate), tournament_size(tour_size), num_elites(elites), crossover_type(cross_type), num_generations(num_gen) {
    }
};
#endif //RESULT_H
