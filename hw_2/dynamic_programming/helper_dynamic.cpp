//
// Created by josip on 23/11/2024.
//

#include "helper_dynamic.h"

#include <chrono>
#include <fstream>
#include <iostream>

#include "dynamic_programming.h"

void create_csv_dynamic_programming(const std::vector<ResultDynamicProgramming> &combinedResults) {
    std::ofstream file("data/resultsDP.csv");
    file << "n,type,runtime_microseconds\n";
    for (const auto &result : combinedResults) {
        file << result.n << "," << instanceTypeToString(result.type) << "," << result.measuredTime << "\n";
    }
}

ResultDynamicProgramming call_dynamic_programming(const InstanceSize &instances) {
    long long total_duration = 0;

    for (const auto &example: instances.exampleList.instance) {
        constexpr int NUM_RUNS = 1;
        long long current_duration = 0;
        for (int run = 0; run < NUM_RUNS; ++run) {
            const auto [fst, snd] = calculate_dynamic_programming(example);
            if (fst != instances.exampleList.solutionMap.at(example.ID)) {
                std::cout << "Error found in instance " << example.ID << std::endl;
            }
            current_duration += snd;
        }
        total_duration += current_duration / NUM_RUNS;
    }

    const long long avg_duration_ms = (total_duration);

    return {instances.n, instances.type, avg_duration_ms};
}
