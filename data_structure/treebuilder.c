//
// Created by Ladence on 01.04.2018.
//
#include "datastructure.h"
#include "treebuilder.h"
int free_index = 1;

int add_node(int index, unsigned int weight) {
    int i = num_nodes++;
    // move nodes with largest weight to the right
    while (i > 0 && nodes[i].weight > weight) {
        memcpy(&nodes[i + 1], &nodes[i], sizeof(node_t));
        if (nodes[i].index < 0) {
            ++leaf_index[-nodes[i].index];
        } else {
            ++parent_index[nodes[i].index];
        }
        --i;
    }
    // add new node to its rightful place
    ++i;
    nodes[i].index = index;
    nodes[i].weight = weight;
    if (index < 0) {
        leaf_index[-index] = i;
    } else {
        parent_index[index] = i;
    }
}

void add_leaves() {
    int i, freq;
    for (i = 0; i < NUM_ALPHABETS; i++) {
        freq = frequency[i];
        if (freq > 0) {
            add_node(-(i + 1), freq);
        }
    }
}

void build_tree() {
    int a, b, index;
    while (free_index < num_nodes) {
        a = free_index++;
        b = free_index++;
        index = add_node(b/2, nodes[a].weight + nodes[b].weight);
        parent_index[b/2] = index;
    }
}
