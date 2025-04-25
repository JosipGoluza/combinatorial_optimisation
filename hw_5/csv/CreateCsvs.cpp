//
// Created by josip on 08/01/2025.
//

#include "CreateCsvs.h"

#include <fstream>
#include "../model/Algorithm.h"

void create_csv(const std::vector<ResultGeneticAlgorithm> &resultVector, const std::string &filename) {
    std::ofstream file(filename);

    file <<
            "type,measured_time,variable_number,clauses_number,average_error,best_fitness_error,population_size,tournament_size,num_elites,num_generations,parameter_changed,max_attempts,mutation_rate,crossover_rate\n";

    for (const auto &result: resultVector) {
        file << instanceTypeToString(result.type) << ","
                << result.measuredTime << ","
                << result.variable_number << ","
                << result.clauses_number << ","
                << result.average_error << ","
                << result.smallest_error << ","
                << result.population_size << ","
                << result.tournament_size << ","
                << result.num_elites << ","
                << result.num_generations << ","
                << parameterChangeToFolder(result.parameter_changed) << ","
                << result.max_attempts << ","
                << result.mutation_rate << ","
                << result.crossover_rate << "\n";
    }
}

void create_csv_genetic_algorithm(const std::vector<ResultGeneticAlgorithm> &resultVector) {
    std::vector<ResultGeneticAlgorithm> resultsNone;
    std::vector<ResultGeneticAlgorithm> resultsPopulationSize;
    std::vector<ResultGeneticAlgorithm> resultsTournamentSize;
    std::vector<ResultGeneticAlgorithm> resultsNumElites;
    std::vector<ResultGeneticAlgorithm> resultsNumGenerations;
    std::vector<ResultGeneticAlgorithm> resultsMaxAttempts;
    std::vector<ResultGeneticAlgorithm> resultsMutationRate;
    std::vector<ResultGeneticAlgorithm> resultsCrossoverRate;

    for (const auto &result: resultVector) {
        switch (result.parameter_changed) {
            case NONE:
                resultsNone.push_back(result);
                break;
            case POPULATION_SIZE:
                resultsPopulationSize.push_back(result);
                break;
            case TOURNAMENT_SIZE:
                resultsTournamentSize.push_back(result);
                break;
            case NUM_ELITES:
                resultsNumElites.push_back(result);
                break;
            case NUM_GENERATIONS:
                resultsNumGenerations.push_back(result);
                break;
            case MAX_ATTEMPTS:
                resultsMaxAttempts.push_back(result);
                break;
            case MUTATION_RATE:
                resultsMutationRate.push_back(result);
                break;
            case CROSSOVER_RATE:
                resultsCrossoverRate.push_back(result);
                break;
            default: break;
        }
    }

    if (!resultsNone.empty()) {
        create_csv(resultsNone, "results/none/resultsGA_none.csv");
    }
    if (!resultsPopulationSize.empty()) {
        create_csv(resultsPopulationSize, "results/population/resultsGA_population_size.csv");
    }
    if (!resultsTournamentSize.empty()) {
        create_csv(resultsTournamentSize, "results/tournament/resultsGA_tournament_size.csv");
    }
    if (!resultsNumElites.empty()) {
        create_csv(resultsNumElites, "results/elites/resultsGA_num_elites.csv");
    }
    if (!resultsNumGenerations.empty()) {
        create_csv(resultsNumGenerations, "results/generations/resultsGA_num_generations.csv");
    }
    if (!resultsMaxAttempts.empty()) {
        create_csv(resultsMaxAttempts, "results/attempts/resultsGA_max_attempts.csv");
    }
    if (!resultsMutationRate.empty()) {
        create_csv(resultsMutationRate, "results/mutation/resultsGA_mutation_rate.csv");
    }
    if (!resultsCrossoverRate.empty()) {
        create_csv(resultsCrossoverRate, "results/crossover/resultsGA_crossover_rate.csv");
    }
}
