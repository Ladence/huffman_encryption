#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
int *frequency = NULL;
int num_alphabets = 0;
int num_active = 0;
unsigned int original_size = 0;

node_t *nodes = NULL;
int num_nodes = 0;
int *leaf_index = NULL;
int *parent_index = NULL;

void determine_frequency(FILE *f) {
    int c;
    while ((c = fgetc(f)) != EOF) {
        ++frequency[c];
        ++original_size;
    }
    for (c = 0; c < NUM_ALPHABETS; c++) {
        if (frequency[c] > 0) {
            num_active++;
        }
    }
}

void init() {
    frequency = (int *)calloc(2*NUM_ALPHABETS, sizeof(int));
    leaf_index = frequency + NUM_ALPHABETS - 1;
}

void allocate_tree() {
    nodes = (node_t *)calloc(2 * num_active, sizeof(node_t));
    parent_index = (int *) calloc (num_active, sizeof(int));
}

void finalize() {
    free(parent_index);
    free(frequency);
    free(nodes);
}