//
// Created by josip on 17/12/2024.
//

#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>
#include <random>

#include "model/Instance.h"

// Chromosome representation for Knapsack GA
class Chromosome {
public:
    std::vector<bool> genes;
    int fitness;
    Instance instance;
    mutable int totalWeight;

    Chromosome();
    Chromosome(int size, Instance instance);

    void randomize(std::mt19937& rng);
    static void onePointCrossover(Chromosome& parent1, Chromosome& parent2, std::mt19937& rng);
    static void twoPointCrossover(Chromosome& parent1, Chromosome& parent2, std::mt19937& rng);
    void mutate(double mutation_rate, std::mt19937& rng);
    void repair();
    int calculateTotalWeight();
};

#endif // CHROMOSOME_H