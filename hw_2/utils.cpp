#include "utils.h"

bool compare_by_third_element(const std::array<double, 3> &a, const std::array<double, 3> &b) {
    return a[2] > b[2];
}

bool compare_by_first_element(const std::array<double, 3> &a, const std::array<double, 3> &b) {
    return a[0] > b[0];
}
