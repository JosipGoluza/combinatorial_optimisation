#include "dynamic_programming.h"

#include <limits>
#include <vector>
#include <algorithm>
#include <chrono>

std::pair<int, long long> calculate_dynamic_programming(const Instance &instance) {
    const int n = instance.n;
    const int capacity = instance.capacity;

    int max_cost = 0;
    for (const auto &item : instance.items) {
        max_cost = std::max(max_cost, item.cost);
    }

    const int max_possible_cost = n * max_cost;
    std::vector dp(n + 1, std::vector(max_possible_cost + 1, INT_MAX));

    dp[0][0] = 0;

    const auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= n; ++i) {
        for (int c = 0; c <= max_possible_cost; ++c) {
            dp[i][c] = dp[i - 1][c];

            const int item_cost = instance.items[i - 1].cost;
            const int item_weight = instance.items[i - 1].weight;

            if (c >= item_cost && dp[i - 1][c - item_cost] != INT_MAX) {
                dp[i][c] = std::min(dp[i][c], dp[i - 1][c - item_cost] + item_weight);
            }
        }
    }
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    int max_valid_cost = 0;
    for (int c = 0; c <= max_possible_cost; ++c) {
        if (dp[n][c] <= capacity) {
            max_valid_cost = c;
        }
    }


    return {max_valid_cost, duration.count()};
}
