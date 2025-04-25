//
// Created by josip on 06/01/2025.
//

#ifndef INSTANCE_H
#define INSTANCE_H
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

enum InstanceType {
    A,
    M,
    N,
    Q,
    R
};

inline std::string instanceTypeToString(InstanceType type) {
    switch (type) {
        case A: return "A";
        case M: return "M";
        case N: return "N";
        case Q: return "Q";
        case R: return "R";
        default: return "Unknown";
    }
}

inline InstanceType getInstanceTypeFromFileName(const string& file_name) {
    if (file_name == "wuf-A") {
        return A;
    }
    if (file_name == "wuf-M") {
        return M;
    }
    if (file_name == "wuf-N") {
        return N;
    }
    if (file_name == "wuf-Q") {
        return Q;
    }
    if (file_name == "wuf-R") {
        return R;
    }
    cerr << "Unknown instance type: " << file_name << endl;
    return A;
}

struct Example {
    std::string optimal_solution_name;
    std::vector<int> weights;
    std::vector<std::vector<int>> clauses;
    int optimal_solution;
    string unique_name;

    Example() : optimal_solution(0) {}
    Example(std::string  optimal_solution_name_, const std::vector<int> &weights_, const std::vector<std::vector<int>> &clauses_, const int optimal_solution_, string unique_name)
        : optimal_solution_name(std::move(optimal_solution_name_)), weights(weights_), clauses(clauses_), optimal_solution(optimal_solution_), unique_name(std::move(unique_name)) {
    }
};

struct Instance {
    int variable_number;
    int clauses_number;
    InstanceType instance_type;
    std::vector<Example> exampleList;
};

#endif //INSTANCE_H
