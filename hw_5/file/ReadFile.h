//
// Created by josip on 06/01/2025.
//

#ifndef READFILE_H
#define READFILE_H
#include <string>

#include "../model/Instance.h"

using namespace std;

vector<Instance> readAllFiles(const pair<string,vector<pair<string,string>>>& file_list);

#endif //READFILE_H
