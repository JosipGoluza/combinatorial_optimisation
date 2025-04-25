//
// Created by josip on 30/11/2024.
//

#include "helper_fptas.h"

#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>

#include "fptas_approximation.h"

void create_csv_fptas_approximation(const std::vector<ResultFptasApproximation> &combinedResults) {
    std::ofstream file("data/resultsFA.csv");
    file << "n,type,epsilon,measured_time_microseconds,average_error,maximum_error\n";

    for (const auto &result: combinedResults) {
        file << result.n << ","
                << instanceTypeToString(result.type) << ","
                << result.epsilon << ","
                << result.measuredTime << ","
                << result.average_error << ","
                << result.maximum_error << "\n";
    }
}

Instance clean_instance(const Instance & example) {
    Instance cleaned_instance(example.ID, example.n, example.capacity, std::vector<Item>()); // Initialize with empty items vector
    for (const auto & item : example.items) {
        if (item.weight <= example.capacity) {
            cleaned_instance.items.push_back(item);
        }
    }
    return cleaned_instance;
}

ResultFptasApproximation call_fptas_approximation(InstanceSize &instances, float epsilon) {
    long long total_duration = 0.0;
    std::vector<long double> fptasApproximationAverageErrors;

    for (auto &example: instances.exampleList.instance) {
        constexpr int NUM_RUNS = 1;
        example = clean_instance(example);
        long long current_duration = 0.0;
        for (int run = 0; run < NUM_RUNS; ++run) {

            const auto [fst, snd] = calculate_fptas_approximation(example, epsilon);

            current_duration += snd;

            const auto real_value = static_cast<long double>(instances.exampleList.solutionMap.at(example.ID));
            const long double approximated_value = static_cast<long double>(fst);

            if (real_value != 0.0L) {
                long double difference = std::fabs((approximated_value - real_value) / real_value);

                if (!std::isnan(difference) && !std::isinf(difference)) {
                    fptasApproximationAverageErrors.push_back(difference);
                } else {
                    // Log or handle unexpected values
                    std::cerr << "Warning: Unexpected difference value" << std::endl;
                }
            }
        }
        total_duration += (current_duration / NUM_RUNS);
    }

    std::sort(fptasApproximationAverageErrors.begin(), fptasApproximationAverageErrors.end());
    long double sum_error = 0.0L;
    for (const auto& error : fptasApproximationAverageErrors) {
        sum_error += error;
    }

    int size_of_fptas_error = 0;
    for (const auto &error: fptasApproximationAverageErrors) {
        size_of_fptas_error += 1;
    }
    long double average_error = sum_error / size_of_fptas_error;
    const long double maximum_error = *std::max_element(fptasApproximationAverageErrors.begin(), fptasApproximationAverageErrors.end());
    return {instances.n, instances.type, total_duration, average_error, maximum_error, epsilon};
}
