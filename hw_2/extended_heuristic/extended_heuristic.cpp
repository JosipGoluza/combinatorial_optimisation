#include "extended_heuristic.h"

#include <vector>
#include <algorithm>
#include <array>
#include "../utils.h"

using namespace std;

int calculate_extended_heuristic(const Instance &instance) {
    int n = instance.n;
    vector<array<double, 3>> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i][0] = instance.items[i].cost;
        arr[i][1] = instance.items[i].weight;
        arr[i][2] = arr[i][0] / arr[i][1];
    }

    ranges::sort(arr, compare_by_third_element);

    double weight = 0;
    double cost = 0;
    for (int i = 0; i < n; i++) {
        if (weight + arr[i][1] <= instance.capacity) {
            weight += arr[i][1];
            cost += arr[i][0];
        } else {
            break;
        }
    }

    ranges::sort(arr, compare_by_first_element);

    for (int i = 0; i < n; i++) {
        if (arr[i][1] <= instance.capacity) {
            if (const auto current_cost = arr[i][0]; current_cost > cost) {
                cost = current_cost;
            }
            return static_cast<int>(cost);
        }
    }

    return static_cast<int>(cost);
}

