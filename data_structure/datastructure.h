//
// Created by Ladence on 01.04.2018.
//

#ifndef HUFF_DATASTRUCTURES_H
#define HUFF_DATASTRUCTURES_H

#include <stdint.h>
#include <windef.h>
#include <stdio.h>

#define NUM_ALPHABETS  256

// alphabets
extern int num_active;
extern int *frequency;
extern unsigned int original_size;

typedef struct {
    // -v + 1 (v - byte-value of alphabet)
    int index;
    // frequency if it leaf, and if it internal node - sum of weights of its children
    unsigned int weight;
}node_t;

// tree
extern node_t *nodes;
extern int num_nodes;
extern int *leaf_index;
extern int *parent_index;

// for tree traversal
extern int free_index;

//initialisation tree funcs
void determine_frequency(FILE *);
void init();
void allocate_tree();
void finalize();

#endif //HUFF_DATASTRUCTURES_H
