#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

#include "simple_heuristic.h"
#include "../models.h"

void create_csv_simple_heuristic(const std::vector<ResultSimpleHeuristic> &combinedResults) {
    std::ofstream file("data/resultsSH.csv");
    file << "n,type,measured_time_nanoseconds,average_error,maximum_error\n";

    for (const auto &result: combinedResults) {
        file << result.n << ","
                << instanceTypeToString(result.type) << ","
                << result.measuredTime << ","
                << result.average_error << ","
                << result.maximum_error << "\n";
    }
}

ResultSimpleHeuristic call_simple_heuristic(const InstanceSize &instances) {
    constexpr int NUM_RUNS = 100;
    long long total_duration = 0;
    std::vector<int> simpleHeuristicAverageErrors;

    for (int run = 0; run < NUM_RUNS; ++run) {
        for (const auto &example: instances.exampleList.instance) {
            auto start = std::chrono::high_resolution_clock::now();

            const auto result = calculate_simple_heuristic(example);
            auto difference = instances.exampleList.solutionMap.at(example.ID) - result;
            simpleHeuristicAverageErrors.push_back(difference);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            total_duration += duration.count();
        }
    }

    const long long avg_duration_ms = (total_duration) / (NUM_RUNS);

    const double simpleHeuristicAvg = std::accumulate(simpleHeuristicAverageErrors.begin(),
                                                      simpleHeuristicAverageErrors.end(), 0.0)
                                      / static_cast<double>(simpleHeuristicAverageErrors.size());

    return {
        ResultSimpleHeuristic(
            instances.n,
            instances.type,
            avg_duration_ms,
            simpleHeuristicAvg,
            *std::max_element(simpleHeuristicAverageErrors.begin(), simpleHeuristicAverageErrors.end())
        )
    };
}
