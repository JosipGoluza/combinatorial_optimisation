#include "file_utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include <map>

std::string readFileContent(const std::string &filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filepath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int getNFromDirectory(const std::string &instance, InstanceType directory) {
    size_t startPos = std::strlen(instanceTypeToString(directory));
    size_t endPos = instance.find('_');

    std::string numberStr = instance.substr(startPos, endPos - startPos);

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

    for (size_t index = 0; index < instances.size(); ++index) {
        std::istringstream iss(instances[index]);
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

std::vector<InstanceSize> readAllFiles(InstanceType directory,
                                       const std::vector<std::pair<std::string, std::string> > &pairList) {
    std::vector<InstanceSize> results;
    std::string dirPrefix = "data/";
    dirPrefix += instanceTypeToString(directory);
    dirPrefix += "/";

    for (const auto &[instanceFile, solutionFile]: pairList) {
        try {
            std::string instanceContent = readFileContent(dirPrefix + instanceFile);
            std::string solutionContent = readFileContent(dirPrefix + solutionFile);

            Examples examples = parseFromFile(instanceContent, solutionContent);

            results.emplace_back(
                getNFromDirectory(instanceFile, directory),
                directory,
                examples
            );
        } catch (const std::exception &e) {
            std::cerr << "Error processing files " << instanceFile << " and "
                    << solutionFile << ": " << e.what() << std::endl;
            continue;
        }
    }

    return results;
}
