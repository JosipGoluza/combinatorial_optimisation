//
// Created by josip on 07/01/2025.
//

#include "Chromosome.h"

#include "GeneticAlgorithm.h"

Chromosome::Chromosome() : fitness(0) {}

Chromosome::Chromosome(const int size) : genes(size, false), fitness(0) {}

void Chromosome::randomize(std::mt19937& rng) {
    std::uniform_real_distribution<> dist(0, 1);
    for (auto && gene : genes) {
        gene = (dist(rng) > 0.5);
    }
}

void Chromosome::mutate(const double mutation_rate, std::mt19937& rng) {
    std::uniform_real_distribution<> dist(0, 1);
    for (size_t i = 0; i < genes.size(); ++i) {
        if (dist(rng) < mutation_rate) {
            genes[i] = !genes[i];
        }
    }
}

