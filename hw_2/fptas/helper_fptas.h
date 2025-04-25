//
// Created by josip on 30/11/2024.
//

#ifndef HELPER_FPTAS_H
#define HELPER_FPTAS_H

#include "../models.h"

void create_csv_fptas_approximation(const std::vector<ResultFptasApproximation> &combinedResults);

ResultFptasApproximation call_fptas_approximation(InstanceSize &instances, float epsilon);

#endif //HELPER_FPTAS_H
