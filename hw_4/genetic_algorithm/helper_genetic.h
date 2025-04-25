//
// Created by josip on 17/12/2024.
//

#ifndef HELPER_GENETIC_H
#define HELPER_GENETIC_H
#include "Example.h"
#include "Result.h"

void create_csv_genetic_algorithm(const std::vector<ResultGeneticAlgorithm> & resultVector);

ResultGeneticAlgorithm call_genetic_algorithm(const Algorithm & algorithm);

#endif //HELPER_GENETIC_H
