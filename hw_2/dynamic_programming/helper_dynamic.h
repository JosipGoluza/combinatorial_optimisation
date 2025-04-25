//
// Created by josip on 23/11/2024.
//

#ifndef HELPER_DYNAMIC_H
#define HELPER_DYNAMIC_H
#include "../models.h"

void create_csv_dynamic_programming(const std::vector<ResultDynamicProgramming> &combinedResults);

ResultDynamicProgramming call_dynamic_programming(const InstanceSize &instances);

#endif //HELPER_DYNAMIC_H
