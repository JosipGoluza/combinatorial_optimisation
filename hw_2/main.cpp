#include "models.h"
#include "file_utils.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>

#include "branch_and_bound.h"
#include "dynamic_programming/helper_dynamic.h"
#include "extended_heuristic/helper_extended.h"
#include "fptas/helper_fptas.h"
#include "simple_heuristics/helper.h"

const std::vector<std::pair<std::string, std::string> > listOfNKPairs = {
    {"NK4_inst.dat", "NK4_sol.dat"},
    {"NK10_inst.dat", "NK10_sol.dat"},
    {"NK15_inst.dat", "NK15_sol.dat"},
    {"NK20_inst.dat", "NK20_sol.dat"},
    {"NK22_inst.dat", "NK22_sol.dat"},
    {"NK25_inst.dat", "NK25_sol.dat"},
    {"NK27_inst.dat", "NK27_sol.dat"},
    {"NK30_inst.dat", "NK30_sol.dat"},
    {"NK32_inst.dat", "NK32_sol.dat"},
    {"NK35_inst.dat", "NK35_sol.dat"},
    {"NK37_inst.dat", "NK37_sol.dat"},
    {"NK40_inst.dat", "NK40_sol.dat"}
};

const std::vector<std::pair<std::string, std::string> > listOfZKCPairs = {
    {"ZKC4_inst.dat", "ZKC4_sol.dat"},
    {"ZKC10_inst.dat", "ZKC10_sol.dat"},
    {"ZKC15_inst.dat", "ZKC15_sol.dat"},
    {"ZKC20_inst.dat", "ZKC20_sol.dat"},
    {"ZKC22_inst.dat", "ZKC22_sol.dat"},
    {"ZKC25_inst.dat", "ZKC25_sol.dat"},
    {"ZKC27_inst.dat", "ZKC27_sol.dat"},
    {"ZKC30_inst.dat", "ZKC30_sol.dat"},
    {"ZKC32_inst.dat", "ZKC32_sol.dat"},
    {"ZKC35_inst.dat", "ZKC35_sol.dat"},
    {"ZKC37_inst.dat", "ZKC37_sol.dat"},
    {"ZKC40_inst.dat", "ZKC40_sol.dat"}
};

const std::vector<std::pair<std::string, std::string> > listOfZKWPairs = {
    {"ZKW4_inst.dat", "ZKW4_sol.dat"},
    {"ZKW10_inst.dat", "ZKW10_sol.dat"},
    {"ZKW15_inst.dat", "ZKW15_sol.dat"},
    {"ZKW20_inst.dat", "ZKW20_sol.dat"},
    {"ZKW22_inst.dat", "ZKW22_sol.dat"},
    {"ZKW25_inst.dat", "ZKW25_sol.dat"},
    {"ZKW27_inst.dat", "ZKW27_sol.dat"},
    {"ZKW30_inst.dat", "ZKW30_sol.dat"},
    {"ZKW32_inst.dat", "ZKW32_sol.dat"},
    {"ZKW35_inst.dat", "ZKW35_sol.dat"},
    {"ZKW37_inst.dat", "ZKW37_sol.dat"},
    {"ZKW40_inst.dat", "ZKW40_sol.dat"}
};

AllResults goThroughFiles(const std::vector<InstanceSize> &input, CompileMethods compileMethodsFlag) {
    std::vector<ResultSimpleHeuristic> resultsSH;
    std::vector<ResultExtendedHeuristic> resultsEH;
    std::vector<ResultDynamicProgramming> resultsDP;
    std::vector<ResultFptasApproximation> resultsFA;

    for (auto instances: input) {
        if (compileMethodsFlag.simpleHeuristic == true) {
            auto simple_heuristic = call_simple_heuristic(instances);
            resultsSH.push_back(simple_heuristic);
        }

        if (compileMethodsFlag.extendedHeuristic == true) {
            auto extended_heuristic = call_extended_heuristic(instances);
            resultsEH.push_back(extended_heuristic);
        }

        if (compileMethodsFlag.dynamicProgramming == true) {
            auto dynamic_programming = call_dynamic_programming(instances);
            resultsDP.push_back(dynamic_programming);
        }

        for (std::vector<float> epsilon_list = {0.01, 0.05, 0.1, 0.2, 0.5, 0.7}; const auto epsilon: epsilon_list) {
            if (compileMethodsFlag.fptasApproximation == true) {
                auto fptas_approximation = call_fptas_approximation(instances, epsilon);
                resultsFA.push_back(fptas_approximation);
            }
        }
    }
    return {resultsSH, resultsEH, resultsDP, resultsFA};
}
void distributeResults(const AllResults &resultsNK, const AllResults &resultsZKC, const AllResults &resultsZKW, const CompileMethods compileMethodsFlag) {
    std::vector<ResultSimpleHeuristic> combined_results_simple_heuristics;
    std::vector<ResultExtendedHeuristic> combined_results_extended_heuristics;
    std::vector<ResultDynamicProgramming> combined_results_dynamic_programming;
    std::vector<ResultFptasApproximation> combined_results_fptas_approximation;

    combined_results_simple_heuristics.insert(combined_results_simple_heuristics.end(),
                                              resultsNK.simpleHeuristicResults.begin(),
                                              resultsNK.simpleHeuristicResults.end());
    combined_results_simple_heuristics.insert(combined_results_simple_heuristics.end(),
                                              resultsZKC.simpleHeuristicResults.begin(),
                                              resultsZKC.simpleHeuristicResults.end());
    combined_results_simple_heuristics.insert(combined_results_simple_heuristics.end(),
                                              resultsZKW.simpleHeuristicResults.begin(),
                                              resultsZKW.simpleHeuristicResults.end());

    combined_results_extended_heuristics.insert(combined_results_extended_heuristics.end(),
                                                resultsNK.extendedHeuristicResults.begin(),
                                                resultsNK.extendedHeuristicResults.end());
    combined_results_extended_heuristics.insert(combined_results_extended_heuristics.end(),
                                                resultsZKC.extendedHeuristicResults.begin(),
                                                resultsZKC.extendedHeuristicResults.end());
    combined_results_extended_heuristics.insert(combined_results_extended_heuristics.end(),
                                                resultsZKW.extendedHeuristicResults.begin(),
                                                resultsZKW.extendedHeuristicResults.end());

    combined_results_dynamic_programming.insert(combined_results_dynamic_programming.end(),
                                                resultsNK.dynamicProgrammingResults.begin(),
                                                resultsNK.dynamicProgrammingResults.end());
    combined_results_dynamic_programming.insert(combined_results_dynamic_programming.end(),
                                                resultsZKC.dynamicProgrammingResults.begin(),
                                                resultsZKC.dynamicProgrammingResults.end());
    combined_results_dynamic_programming.insert(combined_results_dynamic_programming.end(),
                                                resultsZKW.dynamicProgrammingResults.begin(),
                                                resultsZKW.dynamicProgrammingResults.end());

    combined_results_fptas_approximation.insert(combined_results_fptas_approximation.end(),
                                                resultsNK.fptasApproximationResults.begin(),
                                                resultsNK.fptasApproximationResults.end());
    combined_results_fptas_approximation.insert(combined_results_fptas_approximation.end(),
                                                resultsZKC.fptasApproximationResults.begin(),
                                                resultsZKC.fptasApproximationResults.end());
    combined_results_fptas_approximation.insert(combined_results_fptas_approximation.end(),
                                                resultsZKW.fptasApproximationResults.begin(),
                                                resultsZKW.fptasApproximationResults.end());


    if (compileMethodsFlag.simpleHeuristic == true)
        create_csv_simple_heuristic(combined_results_simple_heuristics);
    if (compileMethodsFlag.extendedHeuristic == true)
        create_csv_extended_heuristic(combined_results_extended_heuristics);
    if (compileMethodsFlag.dynamicProgramming == true)
        create_csv_dynamic_programming(combined_results_dynamic_programming);
    if (compileMethodsFlag.fptasApproximation == true)
        create_csv_fptas_approximation(combined_results_fptas_approximation);
}

int main() {
    const auto start = std::chrono::high_resolution_clock::now();

    // setting flags to set which methods to compile currently
    const auto compileMethodsFlag = CompileMethods(false, false,true, false, false);

    if (compileMethodsFlag.branchAndBound == true)
        do_branch_and_bound();

    const auto inputNK = readAllFiles(InstanceType::NK, listOfNKPairs);
    const auto inputZKC = readAllFiles(InstanceType::ZKC, listOfZKCPairs);
    const auto inputZKW = readAllFiles(InstanceType::ZKW, listOfZKWPairs);

    const auto resultsNK = goThroughFiles(inputNK, compileMethodsFlag);
    const auto resultsZKC = goThroughFiles(inputZKC, compileMethodsFlag);
    const auto resultsZKW = goThroughFiles(inputZKW, compileMethodsFlag);

    distributeResults(resultsNK, resultsZKC, resultsZKW, compileMethodsFlag);

    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Compilation time: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}
