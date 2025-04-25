#include "chromosome.h"

#include <algorithm>
#include <iostream>

// Constructor implementations
Chromosome::Chromosome() : fitness(0), totalWeight(0) {}
Chromosome::Chromosome(const int size, Instance instance) : genes(size, false), fitness(0), instance(std::move(instance)), totalWeight(0) {}

// Method implementations
void Chromosome::randomize(std::mt19937& rng) {
    std::uniform_real_distribution<> dist(0, 1);
    for (auto && gene : genes) {
        gene = (dist(rng) > 0.5);
    }
}

void Chromosome::onePointCrossover(Chromosome& parent1, Chromosome& parent2, std::mt19937& rng) {
    std::uniform_int_distribution<> crossover_point(1, static_cast<int>(parent1.genes.size() - 1));
    const int point = crossover_point(rng);

    // Swap genes after crossover point
    for (int i = point; i < parent1.genes.size(); ++i) {
        const bool temp = parent1.genes[i];
        parent1.genes[i] = parent2.genes[i];
        parent2.genes[i] = temp;
    }
}

void Chromosome::twoPointCrossover(Chromosome& parent1, Chromosome& parent2, std::mt19937& rng) {
    const int size = static_cast<int>(parent1.genes.size());
    std::uniform_int_distribution<> point_dist(1, size - 1);

    // Generate two unique crossover points
    int point1 = point_dist(rng);
    int point2 = point_dist(rng);
    if (point1 > point2) std::swap(point1, point2);

    // Swap genes between crossover points
    for (int i = point1; i < point2; ++i) {
        const bool temp = parent1.genes[i];
        parent1.genes[i] = parent2.genes[i];
        parent2.genes[i] = temp;
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

void Chromosome::repair() {
    if (int total_weight = calculateTotalWeight(); total_weight > instance.capacity) {
        std::vector<std::pair<double, int>> ratio_indices;
        for (size_t i = 0; i < genes.size(); ++i) {
            if (genes[i]) {
                double ratio = static_cast<double>(instance.items[i].cost) / instance.items[i].weight;
                ratio_indices.emplace_back(ratio, i);
            }
        }

        // Sort by ratio ascending (we'll remove worst items first)
        ranges::sort(ratio_indices);

        // Remove items until we're under capacity
        for (const auto& [ratio, idx] : ratio_indices) {
            if (total_weight <= instance.capacity) break;
            genes[idx] = false;
            total_weight -= instance.items[idx].weight;
        }
    }
}

int Chromosome::calculateTotalWeight() {
    int total_weight = 0;
    for (size_t i = 0; i < genes.size(); ++i) {
        if (genes[i]) {
            total_weight += instance.items[i].weight;
        }
    }
    return total_weight;
}