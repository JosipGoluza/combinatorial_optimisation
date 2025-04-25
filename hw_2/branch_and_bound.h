#ifndef BRANCH_AND_BOUND_H
#define BRANCH_AND_BOUND_H
#include <vector>

#include "models.h"

void do_branch_and_bound();

int calculateBranchAndBound(const Instance &instance);

int knapsackBranchAndBound(int capacity, const std::vector<Item> &items, int index, int currentValue,
                           int &currently_best_solution);

int getSumOfUndecidedItems(const std::vector<Item> &items, int index);

#endif
