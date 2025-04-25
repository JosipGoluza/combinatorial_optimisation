//
// Created by josip on 07/01/2025.
//

#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>
#include <random>

#include "../model/Instance.h"

class Chromosome {
public:
    std::vector<bool> genes;
    int fitness;

    Chromosome();
    explicit Chromosome(int size);

    void randomize(std::mt19937& rng);
    void mutate(double mutation_rate, std::mt19937& rng);
};

#endif //CHROMOSOME_H
