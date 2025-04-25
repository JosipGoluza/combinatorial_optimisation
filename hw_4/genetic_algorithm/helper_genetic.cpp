//
// Created by josip on 17/12/2024.
//

#include "helper_genetic.h"

#include <chrono>
#include <cmath>
#include <fstream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <array>
#include <filesystem>

#include "knapsack_ga.h"
using namespace std;

#include "calculate_genetic.h"

void create_csv_genetic_algorithm(const std::vector<ResultGeneticAlgorithm> &resultVector) {
    std::ofstream file("data/resultsGA.csv");

    file << "n,type,measured_time_milliseconds,average_error,population_size,mutation_rate,crossover_rate,tournament_size,num_elites,crossover_type,num_generations\n";

    for (const auto &result: resultVector) {
        file << result.n << ","
                << instanceTypeToString(result.type) << ","
                << result.measuredTime << ","
                << result.average_error << ","
                << result.population_size << ","
                << result.mutation_rate << ","
                << result.crossover_rate << ","
                << result.tournament_size << ","
                << result.num_elites << ","
                << crossoverTypeToString(result.crossover_type) << ","
                << result.num_generations << "\n";
    }
}

KnapsackGA mapAlgorithmToKnapsackGA(const Algorithm & algorithm, const Instance & example) {
    return {example, algorithm.population_size, algorithm.num_generations, algorithm.crossover_rate,
                      algorithm.mutation_rate, algorithm.tournament_size, algorithm.num_elites, algorithm.crossover_type};
}

ResultGeneticAlgorithm call_genetic_algorithm(const Algorithm & algorithm) {
    long long total_duration = 0;
    std::vector<long double> simpleHeuristicAverageErrors;

    for (const Instance &example: algorithm.exampleList.instance) {
        KnapsackGA knapsack_ga = mapAlgorithmToKnapsackGA(algorithm, example);

        auto start = std::chrono::high_resolution_clock::now();

        const int result = calculate_genetic_algorithm(knapsack_ga);
        const int real_value = algorithm.exampleList.solutionMap.at(example.ID);
        if ( real_value == 0) {
            simpleHeuristicAverageErrors.push_back(0);
        } else {
            const long double difference = std::fabs(real_value - result) / real_value;
            if (result == 0) {
                std::cout << "Valid result could not be found" << std::endl;
            }
            //std::cout << "Real value: " << real_value << " - Result: " << result << " - Difference: " << difference << std::endl;
            simpleHeuristicAverageErrors.push_back(difference);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_duration += duration.count();
    }

    // to miliseconds
    const long long avg_duration_ms = (total_duration) / 1000000;

    const long double simpleHeuristicAvg = std::accumulate(simpleHeuristicAverageErrors.begin(),
                                                           simpleHeuristicAverageErrors.end(), 0.0L)
                                           / static_cast<long double>(simpleHeuristicAverageErrors.size());

    return {
        ResultGeneticAlgorithm(
            algorithm.n,
            algorithm.type,
            avg_duration_ms,
            simpleHeuristicAvg,
            algorithm.population_size,
            algorithm.mutation_rate,
            algorithm.crossover_rate,
            algorithm.tournament_size,
            algorithm.num_elites,
            algorithm.crossover_type,
            algorithm.num_generations
        )
    };
}

