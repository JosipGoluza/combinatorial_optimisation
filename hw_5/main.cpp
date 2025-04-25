#include "main.h"

#include <chrono>
#include <filesystem>
#include <future>
#include <iostream>
#include <thread>

#include "algorithm_properties/FillProperties.h"
#include "csv/CreateCsvs.h"
#include "file/ReadFile.h"
#include "helper/HelperGenetic.h"
#include "model/Result.h"
#include "thread_pool/ThreadPool.h"

/*std::vector<ResultGeneticAlgorithm> goThroughFiles(const std::vector<Algorithm>& vector) {
    // Create a thread pool with number of threads equal to hardware concurrency
    ThreadPool pool(std::thread::hardware_concurrency());

    std::vector<future<ResultGeneticAlgorithm>> futures;
    std::vector<ResultGeneticAlgorithm> resultsGA;

    // Submit tasks to thread pool
    for (const Algorithm& instances : vector) {
        futures.push_back(
            pool.enqueue([&instances]() {
                const ResultGeneticAlgorithm result = call_genetic_algorithm(instances);
                std::cout << "Finished an Algorithm" << std::endl;
                return result;
            })
        );
    }

    // Collect results
    for (auto& future : futures) {
        resultsGA.push_back(future.get());
    }

    return resultsGA;
}*/

std::vector<ResultGeneticAlgorithm> goThroughFiles(const std::vector<Algorithm> & vector) {
    std::vector<ResultGeneticAlgorithm> resultsGA;

    for (const Algorithm& instances: vector) {
        ResultGeneticAlgorithm genetic_algorithm = call_genetic_algorithm(instances);
        resultsGA.push_back(genetic_algorithm);
        std::cout << "Finished an Algorithm" << std::endl;
    }
    return resultsGA;
}

void distributeResults(const vector<ResultGeneticAlgorithm> & vector) {
    create_csv_genetic_algorithm(vector);
}

void delete_folder_content(const string &folder_name) {
    try {
        if (std::filesystem::exists(folder_name)) {
            std::filesystem::remove_all(folder_name);
            std::cout << "Deleted the 'results' folder successfully." << std::endl;
        } else {
            std::cout << "'results' folder does not exist." << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error deleting 'results' folder: " << e.what() << std::endl;
    }
    std::filesystem::create_directory(folder_name);
}

int main() {
    delete_folder_content("results");

    vector<Instance> all_instances;

    const auto start = std::chrono::high_resolution_clock::now();

    if (!listOfN.second.empty()) {
        vector<Instance> instancesN = readAllFiles(listOfN);
        all_instances.insert(all_instances.end(), instancesN.begin(), instancesN.end());
    }
    if (!listOfM.second.empty()) {
        vector<Instance> instancesM = readAllFiles(listOfM);
        all_instances.insert(all_instances.end(), instancesM.begin(), instancesM.end());
    }
    if (!listOfA.second.empty()) {
        vector<Instance> instancesA = readAllFiles(listOfA);
        all_instances.insert(all_instances.end(), instancesA.begin(), instancesA.end());
    }
    if (!listOfQ.second.empty()) {
        vector<Instance> instancesQ = readAllFiles(listOfQ);
        all_instances.insert(all_instances.end(), instancesQ.begin(), instancesQ.end());
    }
    if (!listOfR.second.empty()) {
        vector<Instance> instancesR = readAllFiles(listOfR);
        all_instances.insert(all_instances.end(), instancesR.begin(), instancesR.end());
    }

    const vector<Algorithm> all_algorithms = fill_algorithm_properties(all_instances);

    const std::vector<ResultGeneticAlgorithm> results = goThroughFiles(all_algorithms);

    distributeResults(results);

    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Compilation time: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}
