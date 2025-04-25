#include "helper_extended.h"

#include <chrono>
#include <numeric>
#include <fstream>
#include <vector>

#include "extended_heuristic.h"

void create_csv_extended_heuristic(const std::vector<ResultExtendedHeuristic> &combinedResults) {
    std::ofstream file("data/resultsEH.csv");
    file << "n,type,measured_time_nanoseconds,average_error,maximum_error\n";

    for (const auto &result: combinedResults) {
        file << result.n << ","
                << instanceTypeToString(result.type) << ","
                << result.measuredTime << ","
                << result.average_error << ","
                << result.maximum_error << "\n";
    }
}

ResultExtendedHeuristic call_extended_heuristic(const InstanceSize &instances) {
    constexpr int NUM_RUNS = 100;
    long long total_duration = 0;
    std::vector<int> extendedHeuristicAverageErrors;

    for (int run = 0; run < NUM_RUNS; ++run) {
        for (const auto &example: instances.exampleList.instance) {
            auto start = std::chrono::high_resolution_clock::now();

            const auto result = calculate_extended_heuristic(example);
            auto difference = instances.exampleList.solutionMap.at(example.ID) - result;
            extendedHeuristicAverageErrors.push_back(difference);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            total_duration += duration.count();
        }
    }

    const long long avg_duration_ms = (total_duration) / (NUM_RUNS);

    const double extendedHeuristicAvg = std::accumulate(extendedHeuristicAverageErrors.begin(),
                                                      extendedHeuristicAverageErrors.end(), 0.0)
                                      / static_cast<double>(extendedHeuristicAverageErrors.size());

    return {
        ResultExtendedHeuristic(
            instances.n,
            instances.type,
            avg_duration_ms,
            extendedHeuristicAvg,
            *std::max_element(extendedHeuristicAverageErrors.begin(), extendedHeuristicAverageErrors.end())
        )
    };
}
