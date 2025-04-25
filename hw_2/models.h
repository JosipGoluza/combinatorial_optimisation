#ifndef MODELS_H
#define MODELS_H
#include <map>
#include <utility>
#include <vector>


struct Item {
    int weight;
    int cost;

    Item(const int w, const int c) : weight(w), cost(c) {
    }
};

struct Instance {
    int ID;
    int n;
    int capacity;
    std::vector<Item> items;

    Instance(const int ID, const int n_, const int cap, const std::vector<Item> &items_)
        : ID(ID), n(n_), capacity(cap), items(items_) {
    }
};

struct Examples {
    std::vector<Instance> instance;
    std::map<int, int> solutionMap;

    Examples(std::vector<Instance> inst, const std::map<int, int> &solMap)
        : instance(std::move(inst)), solutionMap(solMap) {
    }
};

enum class InstanceType {
    NK,
    ZKC,
    ZKW,
};

static const char *instanceTypeToString(InstanceType type) {
    switch (type) {
        case InstanceType::NK: return "NK";
        case InstanceType::ZKC: return "ZKC";
        case InstanceType::ZKW: return "ZKW";
        default: return "Unknown";
    }
}

struct InstanceSize {
    int n;
    InstanceType type;
    Examples exampleList;

    InstanceSize(const int n_, const InstanceType t, Examples examples)
        : n(n_), type(t), exampleList(std::move(examples)) {
    }
};

struct ResultBAB {
    int n;
    InstanceType type;
    long long measuredTime;

    ResultBAB(const int n_, const InstanceType t, const long long mt)
        : n(n_), type(t), measuredTime(mt) {
    }
};

struct Result {
    int n;
    InstanceType type;
    long long measuredTime;

    Result(const int n_, const InstanceType t, const long long mt)
        : n(n_), type(t), measuredTime(mt) {
    }
};

struct ResultSimpleHeuristic : Result {
    double average_error;
    int maximum_error;

    ResultSimpleHeuristic(const int n_, const InstanceType t, const long long mt, const double ar, const int me)
        : Result(n_, t, mt), average_error(ar), maximum_error(me) {
    }
};

struct ResultExtendedHeuristic : Result {
    double average_error;
    int maximum_error;

    ResultExtendedHeuristic(const int n_, const InstanceType t, const long long mt, const double ar, const int me)
        : Result(n_, t, mt), average_error(ar), maximum_error(me) {
    }
};

struct ResultDynamicProgramming : Result {
    ResultDynamicProgramming(const int n_, const InstanceType t, const long long mt)
        : Result(n_, t, mt) {
    }
};

struct ResultFptasApproximation : Result {
    long double average_error;
    long double maximum_error;
    float epsilon;

    ResultFptasApproximation(const int n_, const InstanceType t, const long long mt, const long double ar, const long double me, const float ep)
        : Result(n_, t, mt), average_error(ar), maximum_error(me), epsilon(ep) {}
};

struct AllResults {
    std::vector<ResultSimpleHeuristic> simpleHeuristicResults;
    std::vector<ResultExtendedHeuristic> extendedHeuristicResults;
    std::vector<ResultDynamicProgramming> dynamicProgrammingResults;
    std::vector<ResultFptasApproximation> fptasApproximationResults;

    AllResults(std::vector<ResultSimpleHeuristic> sh, std::vector<ResultExtendedHeuristic> eh, std::vector<ResultDynamicProgramming> dp, std::vector<ResultFptasApproximation> fa)
        : simpleHeuristicResults(std::move(sh)), extendedHeuristicResults(std::move(eh)), dynamicProgrammingResults(std::move(dp)), fptasApproximationResults(std::move(fa)) {
    }
};

struct CompileMethods {
    bool branchAndBound;
    bool simpleHeuristic;
    bool extendedHeuristic;
    bool dynamicProgramming;
    bool fptasApproximation;

    CompileMethods(const bool bab, const bool sh, const bool eh, const bool dp, const bool fa)
        : branchAndBound(bab), simpleHeuristic(sh), extendedHeuristic(eh), dynamicProgramming(dp), fptasApproximation(fa) {}
};

struct InstanceInverseKnapsack {
    int n;
    int i;
    int capacity;
    int c;
    std::vector<int> items;
};

#endif
