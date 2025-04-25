#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <map>

#include "models.h"
#include <string>
#include <vector>

std::vector<InstanceSize> readAllFiles(InstanceType directory, 
    const std::vector<std::pair<std::string, std::string>>& pairList);
int getNFromDirectory(const std::string& instance);
Examples parseFromFile(const std::string& instanceContent,
                                                                  const std::string& solutionContent);

#endif