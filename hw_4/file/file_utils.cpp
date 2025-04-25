//
// Created by josip on 12/12/2024.
//

#include "file_utils.h"



int getNFromDirectory(const std::string &instance, const InstanceType directory) {
    const size_t startPos = std::strlen(instanceTypeToString(directory));
    const size_t endPos = instance.find('_');

    const std::string numberStr = instance.substr(startPos, endPos - startPos);

    return std::stoi(numberStr);
}

Examples parseFromFile(const std::string &instanceContent,
                                   const std::string &solutionContent) {
    std::vector<Instance> instancesList;
    std::map<int, int> solutionMap;
    std::vector<std::string> instances;
    std::vector<std::string> solutions;

    std::istringstream instanceStream(instanceContent);
    std::istringstream solutionStream(solutionContent);
    std::string line;

    while (std::getline(instanceStream, line)) {
        if (!line.empty()) {
            instances.push_back(line);
        }
    }
    if (!instances.empty()) {
        instances.pop_back();
    }

    while (std::getline(solutionStream, line)) {
        if (!line.empty()) {
            solutions.push_back(line);
        }
    }
    if (!solutions.empty()) {
        solutions.pop_back();
    }

    for (const auto & instance : instances) {
        std::istringstream iss(instance);
        std::vector<std::string> instanceValues;
        std::string value;

        while (iss >> value) {
            instanceValues.push_back(value);
        }

        int id = std::stoi(instanceValues[0]);
        int n = std::stoi(instanceValues[1]);
        int capacity = std::stoi(instanceValues[2]);

        std::vector<Item> items;
        for (size_t i = 3; i < instanceValues.size(); i += 2) {
            int weight = std::stoi(instanceValues[i]);
            int cost = std::stoi(instanceValues[i + 1]);
            items.emplace_back(weight, cost);
        }

        instancesList.emplace_back(id, n, capacity, items);
    }

    for (const auto & index : solutions) {
        std::istringstream iss(index);
        int id;
        std::string dummy;
        int solution;
        iss >> id >> dummy >> solution;
        solutionMap[id] = solution;
    }

    return {instancesList, solutionMap};
}
