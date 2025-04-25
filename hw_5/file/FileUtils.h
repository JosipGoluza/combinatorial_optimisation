//
// Created by josip on 06/01/2025.
//

#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>
#include <filesystem>
#include <map>
using namespace std;
#include "../model/Instance.h"

namespace fs = filesystem;

Instance readFolderContent(const string & folder_name, const InstanceType instance_type, const map<string, int>& solution_content);

std::string readFileContent(const std::string &filepath);

map<string, int> readSolution(const string &file_name);

#endif //FILEUTILS_H
