//
// Created by josip on 06/01/2025.
//

#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
#include <random>
#include <unordered_map>

#include "Chromosome.h"
#include "../model/Algorithm.h"
#include "../model/Instance.h"

class MaxSatGA {
    // GA Parameters
    int population_size;
    int num_generations;
    double crossover_rate;
    double mutation_rate;
    double initial_mutation;
    int tournament_size;
    int num_elites;
    std::unordered_map<std::size_t, int> fitness_cache;
    int variable_number;
    int clauses_number;
    int max_attempts;
    ParameterChange parameter_changed;
    double threshold;

    Example problem_instance;
    std::vector<Chromosome> population;

    std::random_device rd;
    std::mt19937 rng;

    //history
    std::vector<int> best_fitnesses;
    std::vector<double> average_fitnesses;

public:
    MaxSatGA(Example example, int pop_size, int generations, int tour_size, int elites, int variable_number, int clauses_number, int max_attempts, double cross_rate, double mut_rate, ParameterChange parameter_changed, double threshold);

    void onePointCrossover(Chromosome& parent1, Chromosome& parent2, std::mt19937& rng);
    int calculateFitness(const Chromosome& chromosome);
    Chromosome tournamentSelection();
    void initializePopulation();
    double calculateAverageFitness();

    void calculate_new_mutation_rate(int max_fitness, double average_fitness, int gen);

    void check_for_feasible(double current_average_fitness, int max_fitness);

    pair<double, int> evolve();

    [[nodiscard]] string get_type_number() const;

    void create_csv_history() const;
    void repair(std::mt19937& rng, Chromosome& chromosome);
    int scaleClausesToMaxNoChange() const;
};


#endif //GENETICALGORITHM_H
