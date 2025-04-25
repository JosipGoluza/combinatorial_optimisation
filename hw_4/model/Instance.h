//
// Created by josip on 12/12/2024.
//

#ifndef INSTANCE_H
#define INSTANCE_H
#include <vector>

#include "Item.h"
using namespace std;

struct Instance {
    int ID;
    int n;
    int capacity;
    std::vector<Item> items;

    Instance() : ID(0), n(0), capacity(0) {} // Default constructor
    Instance(const int ID, const int n_, const int cap, const std::vector<Item> &items_)
        : ID(ID), n(n_), capacity(cap), items(items_) {
    }
};

enum class InstanceType {
    NK,
    ZKC,
    ZKW,
};

static const char *instanceTypeToString(const InstanceType type) {
    switch (type) {
        case InstanceType::NK: return "NK";
        case InstanceType::ZKC: return "ZKC";
        case InstanceType::ZKW: return "ZKW";
        default: return "Unknown";
    }
}

#endif //INSTANCE_H
