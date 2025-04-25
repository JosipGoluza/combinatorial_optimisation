//
// Created by josip on 30/11/2024.
//

#include "fptas_approximation.h"

#include <chrono>
#include <iostream>
#include <cmath>
#include <climits>

std::pair<long double, long long> calculate_fptas_approximation(const Instance &instance, const float epsilon) {
    const int n = instance.items.size();
    const int capacity = instance.capacity;

    int max_cost = 0;
    for (const auto &item : instance.items) {
        max_cost = std::max(max_cost, item.cost);
    }

    const float K = (epsilon * max_cost) / n;

    std::vector<Item> rounded_items;
    for (const auto &item : instance.items) {
        Item rounded_item = item;
        rounded_item.cost = std::floor(item.cost / K);
        rounded_items.push_back(rounded_item);
    }

    int max_cost_rounded = 0;
    for (const auto &item : rounded_items) {
        max_cost_rounded = std::max(max_cost_rounded, item.cost);
    }

    const int max_possible_cost = n * max_cost_rounded;
    std::vector dp(n + 1, std::vector(max_possible_cost + 1, INT_MAX));

    dp[0][0] = 0;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= n; ++i) {
        for (int c = 0; c <= max_possible_cost; ++c) {
            dp[i][c] = dp[i - 1][c];

            const int item_cost = rounded_items[i - 1].cost;
            const int item_weight = rounded_items[i - 1].weight;

            if (c >= item_cost && dp[i - 1][c - item_cost] != INT_MAX) {
                dp[i][c] = std::min(dp[i][c], dp[i - 1][c - item_cost] + item_weight);
            }
        }
    }
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    long double max_valid_cost = 0;
    for (int c = 0; c <= max_possible_cost; ++c) {
        if (dp[n][c] <= capacity) {
            max_valid_cost = c;
        }
    }

    long double max_valid_cost_scaled = (max_valid_cost * K);
    return {max_valid_cost_scaled, duration.count()};
}
