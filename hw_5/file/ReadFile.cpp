//
// Created by josip on 06/01/2025.
//

#include "ReadFile.h"
#include <filesystem>
#include <map>

#include "FileUtils.h"

vector<Instance> readAllFiles(const pair<string,vector<pair<string,string>>>& file_list) {
    vector<Instance> instances;

    const string outer_folder_name = "../data/" + file_list.first;
    string unique_name = file_list.first;
    const InstanceType instance_type = getInstanceTypeFromFileName(file_list.first);

    for (const auto&[example_folder, optimal_solution] : file_list.second) {
        const string optimal_solution_file = optimal_solution;
        map<string, int> solution_content;
        if (!optimal_solution.empty()) {
            string optimal_inner = outer_folder_name;
            optimal_inner += "/";
            optimal_inner += optimal_solution_file;
            solution_content = readSolution(optimal_inner);
        } else {
            solution_content = {};
        }

        string inner_folder_name = outer_folder_name;
        inner_folder_name += "/";
        inner_folder_name += example_folder;

        // read the content of the files
        Instance instance_content = readFolderContent(inner_folder_name, instance_type, solution_content);
        instances.push_back(instance_content);
    }

    return instances;
}
