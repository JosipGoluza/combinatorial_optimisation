//
// Created by josip on 17/12/2024.
//

#ifndef KNAPSACK_GA_H
#define KNAPSACK_GA_H

#include <vector>
#include <random>
#include <unordered_map>

#include "Instance.h"
#include "algorith_properties/fill_properties.h"
#include "chromosome/chromosome.h"

class KnapsackGA {
    // GA Parameters
    int population_size;
    int num_generations;
    double crossover_rate;
    double mutation_rate;
    int tournament_size;
    int num_elites;
    CrossoverType crossover_type;
    unordered_map<std::size_t, int> fitness_cache;

    // Problem-specific data
    Instance problem_instance;
    std::vector<Chromosome> population;

    // Random number generation
    std::random_device rd;
    std::mt19937 rng;

public:
    KnapsackGA(Instance instance, int pop_size, int generations, double cross_rate, double mut_rate, int tour_size, int elites, CrossoverType cross_type);

    int calculateFitness(const Chromosome& chromosome);
    Chromosome tournamentSelection();
    void initializePopulation();
    double calculateAverageFitness();
    void evolve();
    Chromosome getBestSolution();
    Instance getProblemInstance();
};

#endif //KNAPSACK_GA_H
