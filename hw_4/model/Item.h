//
// Created by josip on 12/12/2024.
//

#ifndef ITEM_H
#define ITEM_H

struct Item {
    int weight;
    int cost;

    Item(const int w, const int c) : weight(w), cost(c) {
    }
};

#endif //ITEM_H
