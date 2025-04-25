//
// Created by josip on 12/12/2024.
//

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <cstring>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Example.h"
#include "Instance.h"

int getNFromDirectory(const std::string &instance, InstanceType directory);

Examples parseFromFile(const std::string &instanceContent, const std::string &solutionContent);

#endif //FILE_UTILS_H
