//
// Created by josip on 12/12/2024.
//

#include "fill_properties.h"

#include <vector>

#include "Example.h"
#include "file/read_file.h"

std::vector<Algorithm> fill_algorithm_properties(const std::vector<FileProperties> &files) {
    std::vector<Algorithm> algorithms;
    for (const FileProperties &file: files) {
        for (const int pop_size: population_size) {
            for (const double mut_rate: mutation_rate) {
                for (const double cross_rate: crossover_rate) {
                    for (const int tour_size: tournament_size) {
                        for (const int elites: num_elites) {
                            for (const CrossoverType cross_type: crossover_type) {
                                for (const int num_generations: num_generations) {
                                    algorithms.emplace_back(
                                        file.n,
                                        file.type,
                                        file.exampleList,
                                        pop_size,
                                        mut_rate,
                                        cross_rate,
                                        tour_size,
                                        elites,
                                        cross_type,
                                        num_generations
                                    );
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return algorithms;
}
