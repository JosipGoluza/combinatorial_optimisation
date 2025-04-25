//
// Created by josip on 06/01/2025.
//

#ifndef RESULT_H
#define RESULT_H
#include <utility>

#include "Instance.h"
#include "Algorithm.h"

struct ExampleResult {
    int best_solution;
    std::vector<int> best_fitnesses;
    std::vector<double> average_fitnesses;

    ExampleResult(const int best_solution, const std::vector<int> &best_fitnesses, const std::vector<double> &average_fitnesses)
        : best_solution(best_solution), best_fitnesses(best_fitnesses), average_fitnesses(average_fitnesses) {}
};

struct Result {
    InstanceType type;
    long long measuredTime;
    int variable_number;
    int clauses_number;

    Result(const InstanceType t, const long long mt, const int vn, const int cn)
        :  type(t), measuredTime(mt), variable_number(vn), clauses_number(cn) {}
};

struct ResultGeneticAlgorithm : Result {
    long double average_error;
    long double smallest_error;
    int population_size;
    int tournament_size;
    int num_elites;
    int num_generations;
    ParameterChange parameter_changed;
    int max_attempts;
    double mutation_rate;
    double crossover_rate;
    double change_threshold;


    ResultGeneticAlgorithm(const InstanceType t, const long long mt, const int vn, const int cn, const long double ae,const int pop_size, const int tour_size, const int elites, const int num_gen, const ParameterChange param_changed, const int max_att, const double mut_rate, const double cross_rate, const double change_threshold, const long double se)
        : Result(t, mt, vn, cn), average_error(ae), smallest_error(se), population_size(pop_size), tournament_size(tour_size), num_elites(elites), num_generations(num_gen), parameter_changed(param_changed), max_attempts(max_att), mutation_rate(mut_rate), crossover_rate(cross_rate), change_threshold(change_threshold) {}
};

#endif //RESULT_H
