#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <string>
#include "models.h"

std::vector<ResultBAB> goThroughFiles(const std::vector<InstanceSize>& input);
void create_csv(const std::vector<ResultBAB>& combinedResults);

extern const std::vector<std::pair<std::string, std::string>> listOfNKPairs;
extern const std::vector<std::pair<std::string, std::string>> listOfZKCPairs;
extern const std::vector<std::pair<std::string, std::string>> listOfZKWPairs;

#endif // MAIN_H