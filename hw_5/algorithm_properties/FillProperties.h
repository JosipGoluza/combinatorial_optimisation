//
// Created by josip on 06/01/2025.
//

#ifndef FILLPROPERTIES_H
#define FILLPROPERTIES_H
#include <array>
#include "../model/Algorithm.h"

using namespace std;

vector<Algorithm> fill_algorithm_properties(const vector<Instance>& instances);

constexpr std::array population_size_list = {100, 500, 1000, 2000, 5000};
constexpr std::array tournament_size_list = {2, 4, 7, 10, 20, 30, 40, 50};
constexpr std::array num_elites_list = {1, 3, 5, 10, 15, 20, 25, 30, 40, 50};
constexpr std::array num_generations_list = {30, 50, 100};
constexpr array max_attempts_list = {200, 250, 300, 400};
constexpr array mutation_rate_list = {0.001, 0.004, 0.007, 0.01, 0.03};
constexpr array crossover_rate_list = {0.7, 0.75, 0.8, 0.85, 0.9, 0.95};
constexpr array change_threshold_list = {0.005, 0.01, 0.02};


// PROMJENIO OVE VRJEDNOSTI, treba provjeriti sta je bolje, malo isprbati nesto vratitt a nesto sotaviti da ne konvergira pre rano ali i da pronade dobra rjesenja
// mozda vratiti max_attempts na 50 pa provjeiti, ostali sam utjecu na konvergnciju?
// mozda vratiti mutation_rate na 0.03 pa bi ubrzalo konvergenciju

constexpr int population_size = 500; // 1000
constexpr int tournament_size = 2; // 3
constexpr int num_elites = 2; // 3
constexpr int num_generations = 300;
constexpr int max_attempts = 50;
constexpr double mutation_rate = 0.05; // 0.05?
constexpr double crossover_rate = 0.9;
constexpr double change_threshold = 0.01;


#endif //FILLPROPERTIES_H
