#ifndef HELPER_EXTENDED_H
#define HELPER_EXTENDED_H

#include "../models.h"

void create_csv_extended_heuristic(const std::vector<ResultExtendedHeuristic> &combinedResults);

ResultExtendedHeuristic call_extended_heuristic(const InstanceSize &instances);

#endif //HELPER_EXTENDED_H
