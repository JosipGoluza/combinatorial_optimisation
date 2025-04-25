//
// Created by josip on 12/12/2024.
//

#ifndef READ_FILE_H
#define READ_FILE_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Example.h"
#include "Instance.h"

struct FileProperties {
    int n;
    InstanceType type;
    Examples exampleList;

    FileProperties(const int n_, const InstanceType t, Examples e)
        : n(n_), type(t), exampleList(std::move(e)) {}
};

std::string readFileContent(const std::string &filepath);

std::vector<FileProperties> readAllFiles(InstanceType directory, const std::vector<std::pair<std::string, std::string> > &pairList);

#endif //READ_FILE_H
