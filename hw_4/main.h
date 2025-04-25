//
// Created by josip on 12/12/2024.
//

#ifndef MAIN_H
#define MAIN_H
#include <vector>
#include <string>
#include <chrono>
#include <iostream>

#include "Example.h"
#include "Instance.h"
#include "Result.h"

const std::vector<std::pair<std::string, std::string>> listOfNK = {
    {"NK30_inst.dat", "NK30_sol.dat"},
    {"NK32_inst.dat", "NK32_sol.dat"},
    {"NK35_inst.dat", "NK35_sol.dat"},
    {"NK37_inst.dat", "NK37_sol.dat"},
    {"NK40_inst.dat", "NK40_sol.dat"},
};

const std::vector<std::pair<std::string, std::string>> listOfZKC = {
    /*{"ZKC30_inst.dat", "ZKC30_sol.dat"},
    {"ZKC32_inst.dat", "ZKC32_sol.dat"},
    {"ZKC35_inst.dat", "ZKC35_sol.dat"},
    {"ZKC37_inst.dat", "ZKC37_sol.dat"},
    {"ZKC40_inst.dat", "ZKC40_sol.dat"},*/
};

const std::vector<std::pair<std::string, std::string>> listOfZKW = {
    /*{"ZKW30_inst.dat", "ZKW30_sol.dat"},
    {"ZKW32_inst.dat", "ZKW32_sol.dat"},
    {"ZKW35_inst.dat", "ZKW35_sol.dat"},
    {"ZKW37_inst.dat", "ZKW37_sol.dat"},
    {"ZKW40_inst.dat", "ZKW40_sol.dat"},*/
};

#endif //MAIN_H
