//
// Created by josip on 30/11/2024.
//

#ifndef FPTAS_APPROXIMATION_H
#define FPTAS_APPROXIMATION_H

#include "../models.h"

std::pair<long double, long long> calculate_fptas_approximation(const Instance &instance, float epsilon);

#endif //FPTAS_APPROXIMATION_H
