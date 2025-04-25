//
// Created by josip on 12/12/2024.
//

#ifndef FILL_PROPERTIES_H
#define FILL_PROPERTIES_H
#include <array>
#include <vector>

#include "Example.h"
#include "file/read_file.h"

std::vector<Algorithm> fill_algorithm_properties(const std::vector<FileProperties>&);

constexpr std::array population_size = {30, 70, 100};
constexpr std::array mutation_rate = {0.01, 0.05, 0.1};
constexpr std::array crossover_rate = {0.8, 0.9, 0.95};
constexpr std::array tournament_size = {2, 4, 6};
constexpr std::array num_elites = {1, 3, 5};
constexpr std::array crossover_type = {ONE_POINT, TWO_POINT};
constexpr std::array num_generations = {30, 50, 100};

#endif //FILL_PROPERTIES_H
