//
// Created by josip on 12/12/2024.
//

#include "read_file.h"

#include "file_utils.h"


std::string readFileContent(const std::string &filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filepath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<FileProperties> readAllFiles(InstanceType directory,
                                       const std::vector<std::pair<std::string, std::string> > &pairList) {
    std::vector<FileProperties> results;
    std::string dirPrefix = "../data/";
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
