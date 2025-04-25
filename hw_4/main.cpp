//
// Created by josip on 12/12/2024.
//

#include "main.h"

#include "algorith_properties/fill_properties.h"
#include "file/read_file.h"
#include "genetic_algorithm/helper_genetic.h"

std::vector<ResultGeneticAlgorithm> goThroughFiles(const std::vector<Algorithm> &input) {
    std::vector<ResultGeneticAlgorithm> resultsSA;

    for (const auto& instances: input) {
        ResultGeneticAlgorithm genetic_algorithm = call_genetic_algorithm(instances);
        resultsSA.push_back(genetic_algorithm);
        std::cout << "Finished an Algorithm" << std::endl;
    }
    return resultsSA;
}

void insert_into_list(auto &combined_results, auto &results) {
    combined_results.insert(combined_results.end(), results.begin(), results.end());
}

void distributeResults(const std::vector<ResultGeneticAlgorithm> & results_nk, const std::vector<ResultGeneticAlgorithm> & results_zkc, const std::vector<ResultGeneticAlgorithm> & results_zkw) {
    std::vector<ResultGeneticAlgorithm> combined_results_genetic_algorithm;

    insert_into_list(combined_results_genetic_algorithm, results_nk);
    insert_into_list(combined_results_genetic_algorithm, results_zkc);
    insert_into_list(combined_results_genetic_algorithm, results_zkw);

    create_csv_genetic_algorithm(combined_results_genetic_algorithm);
}

int main() {
    const auto start = std::chrono::high_resolution_clock::now();

    const auto inputNK = readAllFiles(InstanceType::NK, listOfNK);
    const auto inputZKC = readAllFiles(InstanceType::ZKC, listOfZKC);
    const auto inputZKW = readAllFiles(InstanceType::ZKW, listOfZKW);

    const std::vector<Algorithm> algorithmsNK = fill_algorithm_properties(inputNK);
    const std::vector<Algorithm> algorithmsZKC = fill_algorithm_properties(inputZKC);
    const std::vector<Algorithm> algorithmsZKW = fill_algorithm_properties(inputZKW);

    const std::vector<ResultGeneticAlgorithm> resultsNK = goThroughFiles(algorithmsNK);
    const std::vector<ResultGeneticAlgorithm> resultsZKC = goThroughFiles(algorithmsZKC);
    const std::vector<ResultGeneticAlgorithm> resultsZKW = goThroughFiles(algorithmsZKW);

    distributeResults(resultsNK, resultsZKC, resultsZKW);

    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Compilation time: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}
