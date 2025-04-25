#include "simple_heuristic.h"

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <array>
using namespace std;

int calculate_simple_heuristic(const Instance &instance) {
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

    return static_cast<int>(cost);
}