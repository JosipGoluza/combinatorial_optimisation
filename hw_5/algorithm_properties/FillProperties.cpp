//
// Created by josip on 06/01/2025.
//

#include "FillProperties.h"

vector<Algorithm> fill_algorithm_properties(const vector<Instance> &instances) {
    std::vector<Algorithm> algorithms;

    for (const auto &[variable_number, clauses_number, instance_type, exampleList]: instances) {
        algorithms.emplace_back(
                variable_number,
                clauses_number,
                exampleList,
                instance_type,
                population_size,
                tournament_size,
                num_elites,
                num_generations,
                NONE,
                max_attempts,
                mutation_rate,
                crossover_rate,
                change_threshold
            );
        /*for (const int population_size: population_size_list) {
            algorithms.emplace_back(
                variable_number,
                clauses_number,
                exampleList,
                instance_type,
                population_size,
                tournament_size,
                num_elites,
                num_generations,
                POPULATION_SIZE,
                max_attempts,
                mutation_rate,
                crossover_rate
            );
        }*/
        /*for (const int tournament_size: tournament_size_list) {
            algorithms.emplace_back(
                variable_number,
                clauses_number,
                exampleList,
                instance_type,
                population_size,
                tournament_size,
                num_elites,
                num_generations,
               TOURNAMENT_SIZE,
                max_attempts,
                mutation_rate,
                crossover_rate,
                change_threshold
            );
        }*/
        /*for (const int num_elites: num_elites_list) {
            algorithms.emplace_back(
                    variable_number,
                    clauses_number,
                    exampleList,
                    instance_type,
                    population_size,
                    tournament_size,
                    num_elites,
                    num_generations,
                    NUM_ELITES,
                    max_attempts,
                    mutation_rate,
                    crossover_rate,
                    change_threshold
                );
        }*/
        //for (const int num_generations: num_generations_list) {
            /*algorithms.emplace_back(
                    instance.variable_number,
                    instance.clauses_number,
                    instance.exampleList,
                    instance.instance_type,
                    population_size,
                    tournament_size,
                    num_elites,
                    num_generations,
                    "num_generations",
                    max_attempts,
                    mutation_rate,
                    crossover_rate
                );*/
        //}
        /*for (const int max_attempts: max_attempts_list) {
            algorithms.emplace_back(
                    variable_number,
                    clauses_number,
                    exampleList,
                    instance_type,
                    population_size,
                    tournament_size,
                    num_elites,
                    num_generations,
                    MAX_ATTEMPTS,
                    max_attempts,
                    mutation_rate,
                    crossover_rate,
                    change_threshold
                );
        }*/
        /*for (const double mutation_rate: mutation_rate_list) {
            algorithms.emplace_back(
                    variable_number,
                    clauses_number,
                    exampleList,
                    instance_type,
                    population_size,
                    tournament_size,
                    num_elites,
                    num_generations,
                    MUTATION_RATE,
                    max_attempts,
                    mutation_rate,
                    crossover_rate
                );
        }*/
        /*for (const double crossover_rate: crossover_rate_list) {
            algorithms.emplace_back(
                    variable_number,
                    clauses_number,
                    exampleList,
                    instance_type,
                    population_size,
                    tournament_size,
                    num_elites,
                    num_generations,
                    CROSSOVER_RATE,
                    max_attempts,
                    mutation_rate,
                    crossover_rate,
                    change_threshold
                );
        }*/
        /*for (const double change_threshold: change_threshold_list) {
            algorithms.emplace_back(
                    variable_number,
                    clauses_number,
                    exampleList,
                    instance_type,
                    population_size,
                    tournament_size,
                    num_elites,
                    num_generations,
                    CHANGE_THRESHOLD,
                    max_attempts,
                    mutation_rate,
                    crossover_rate
                );
        }*/
    }
    return algorithms;
}
