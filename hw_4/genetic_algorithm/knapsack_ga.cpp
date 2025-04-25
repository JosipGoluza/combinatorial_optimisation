//
// Created by josip on 17/12/2024.
//

#include "knapsack_ga.h"
#include <algorithm>
#include <random>
#include <utility>
#include <omp.h>

// Constructor
KnapsackGA::KnapsackGA(Instance instance, const int pop_size, const int generations, const double cross_rate, const double mut_rate, const int tour_size, const int elites, const CrossoverType cross_type)
    : population_size(pop_size),
      num_generations(generations),
      crossover_rate(cross_rate),
      mutation_rate(mut_rate),
      tournament_size(tour_size),
      num_elites(elites),
      crossover_type(cross_type),
      problem_instance(std::move(instance)),
        rng(rd())
{}

// Fitness calculation
int KnapsackGA::calculateFitness(const Chromosome& chromosome) {
    const std::size_t hash_key = std::hash<std::vector<bool>>{}(chromosome.genes);

    auto it = fitness_cache.find(hash_key);
    if (it != fitness_cache.end()) {
        return it->second;
    }

    int total_weight = 0;
    int total_cost = 0;

    for (size_t i = 0; i < chromosome.genes.size(); ++i) {
        if (chromosome.genes[i]) {
            total_weight += problem_instance.items[i].weight;
            total_cost += problem_instance.items[i].cost;
        }
    }

    chromosome.totalWeight = total_weight;

    if (total_weight > problem_instance.capacity) {
        return 0;
    }

    fitness_cache[hash_key] = total_cost;
    return total_cost;
}

Chromosome KnapsackGA::tournamentSelection() {
    std::vector<Chromosome> tournament;
    std::uniform_int_distribution<> dist(0, static_cast<int>(population.size()) - 1);

    for (int i = 0; i < tournament_size; ++i) {
        tournament.push_back(population[dist(rng)]);
    }

    return *ranges::max_element(tournament,
                                [](const Chromosome& a, const Chromosome& b) {
                                    return a.fitness < b.fitness;
                                });
}


void KnapsackGA::initializePopulation() {
    population.clear();
    population.reserve(population_size); // Reserve space to avoid reallocations
    for (int i = 0; i < population_size; ++i) {
        Chromosome chromosome(static_cast<int>(problem_instance.items.size()), problem_instance);
        chromosome.randomize(rng);
        chromosome.repair();
        chromosome.fitness = calculateFitness(chromosome);
        population.push_back(chromosome);
    }
}

double KnapsackGA::calculateAverageFitness() {
    double total_fitness = 0.0;
    for (const auto& chromosome : population) {
        total_fitness += chromosome.fitness;
    }
    return total_fitness / static_cast<double>(population.size());
}

void KnapsackGA::evolve() {
    initializePopulation();

    for (int gen = 0; gen < num_generations; ++gen) {
        std::vector<Chromosome> new_population;

        #pragma omp parallel for
        for (size_t i = 0; i < population.size() / 2; ++i) {
            Chromosome parent1 = tournamentSelection();
            Chromosome parent2 = tournamentSelection();

            std::uniform_real_distribution<> dist(0, 1);
            if (dist(rng) < crossover_rate) {
                if (crossover_type == ONE_POINT) {
                    Chromosome::onePointCrossover(parent1, parent2, rng);
                } else {
                    Chromosome::twoPointCrossover(parent1, parent2, rng);
                }
            }

            parent1.mutate(mutation_rate, rng);
            parent2.mutate(mutation_rate, rng);

            //parent1.repair();
            //parent2.repair();

            parent1.fitness = calculateFitness(parent1);
            parent2.fitness = calculateFitness(parent2);

            new_population.push_back(parent1);
            new_population.push_back(parent2);
        }

        if (num_elites > 0) {
            std::vector<Chromosome> elites(num_elites);
            std::partial_sort_copy(population.begin(), population.end(), elites.begin(), elites.end(),
                                   [](const Chromosome& a, const Chromosome& b) {
                                       return a.fitness > b.fitness;
                                   });

            ranges::copy(elites, new_population.begin());
        }

        population = new_population;

        const double current_average_fitness = calculateAverageFitness();
        //std::cout << "Best chromosome" << population[0].fitness << std::endl;
        //std::cout << "Generation " << gen << " - Average fitness: " << current_average_fitness << std::endl;
    }
}

Chromosome KnapsackGA::getBestSolution() {
    const auto best_valid = ranges::max_element(population,
                                                [](const Chromosome& a, const Chromosome& b) {
                                                    return a.fitness < b.fitness;
                                                });
    return *best_valid;
}

Instance KnapsackGA::getProblemInstance() {
    return problem_instance;
}