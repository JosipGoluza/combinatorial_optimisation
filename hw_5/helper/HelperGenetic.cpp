//
// Created by josip on 06/01/2025.
//

#include "HelperGenetic.h"

#include <chrono>
#include <fstream>
#include <numeric>

#include "../model/Result.h"
#include "../model/Algorithm.h"
#include "../genetic_algorithm/GeneticAlgorithm.h"

MaxSatGA mapAlgorithmToMaxSatGA(const Algorithm & algorithm, const Example& example) {
    return {example, algorithm.population_size, algorithm.num_generations, algorithm.tournament_size,
        algorithm.num_elites, algorithm.variable_number, algorithm.clauses_number, algorithm.max_attempts, algorithm.crossover_rate, algorithm.mutation_rate, algorithm.parameter_changed, algorithm.change_threshold};
}

pair<double, int> calculate_genetic_algorithm(MaxSatGA &max_sat_ga) {
    const auto solution = max_sat_ga.evolve();

    max_sat_ga.create_csv_history();

    return solution;
}

ResultGeneticAlgorithm call_genetic_algorithm(const Algorithm & algorithm) {
    long long total_duration = 0;
    std::vector<long double> simpleHeuristicAverageErrors;
    std::vector<long double> simpleHeuristicSmallestErrors;
    bool optimal_exists = true;
    int number_of_unoptimal_instances = 0;

    for (const Example &example: algorithm.exampleList) {
        MaxSatGA knapsack_ga = mapAlgorithmToMaxSatGA(algorithm, example);

        auto start = std::chrono::high_resolution_clock::now();

        const auto result = calculate_genetic_algorithm(knapsack_ga);
        const auto best_average = result.first;
        const auto best_fitness = result.second;
        const int real_value = example.optimal_solution;
        if (real_value == 0) {
            optimal_exists = false;
        } else {
            const long double difference = std::fabs(real_value - best_average) / real_value;
            //std::cout << "Real value: " << real_value << " - Result: " << result << " - Difference: " << difference << std::endl;
            simpleHeuristicAverageErrors.push_back(difference);
            if (difference > 0) {
                std::cout << "Real value: " << real_value << " - Result: " << best_average << " - Difference: " << difference << std::endl;
                number_of_unoptimal_instances++;
            }

            const long double differenceSmallest = std::fabs(real_value - best_fitness) / real_value;
            simpleHeuristicSmallestErrors.push_back(differenceSmallest);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_duration += duration.count();

        //std::cout << "Finished an example" << std::endl;
    }

    //std::cout << "Number of unoptimal instances: " << number_of_unoptimal_instances << std::endl;

    // to miliseconds
    const long long avg_duration_ms = (total_duration) / 1000000;

    long double simpleHeuristicAvg;
    if (!optimal_exists) {
        simpleHeuristicAvg = 0;
    } else {
        simpleHeuristicAvg = std::accumulate(simpleHeuristicAverageErrors.begin(),
                                                           simpleHeuristicAverageErrors.end(), 0.0L)
                                           / static_cast<long double>(simpleHeuristicAverageErrors.size());
    }

    long double simpleHeuristicSmallest;
    if (!optimal_exists) {
        simpleHeuristicSmallest = 0;
    } else {
        simpleHeuristicSmallest = std::accumulate(simpleHeuristicSmallestErrors.begin(),
                                                           simpleHeuristicSmallestErrors.end(), 0.0L)
                                           / static_cast<long double>(simpleHeuristicSmallestErrors.size());
    }

    return {algorithm.instance_type, avg_duration_ms, algorithm.variable_number, algorithm.clauses_number, simpleHeuristicAvg, algorithm.population_size, algorithm.tournament_size, algorithm.num_elites, algorithm.num_generations, algorithm.parameter_changed, algorithm.max_attempts, algorithm.mutation_rate, algorithm.crossover_rate, algorithm.change_threshold, simpleHeuristicSmallest};
}

