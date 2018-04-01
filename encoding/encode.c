//
// Created by Ladence on 01.04.2018.
//

#include <stdio.h>
#include <stdlib.h>
#include "encode.h"
#include "../data_structure/datastructure.h"
#include "../data_structure/treebuilder.h"
#include "../bits_io/iobits.h"

int *stack = NULL;
int stack_top = 0;

int encode(const char *ifile, const char *ofile) {
    FILE *fin, *fout;
    if ((fin = fopen(ifile, "rb")) == NULL) {
        perror("Failed to open input file!");
        return FILE_OPEN_FAIL;
    }
    if ((fout = fopen(ofile, "wb")) == NULL) {
        perror("Failed to open output file!");
        return FILE_OPEN_FAIL;
    }
    determine_frequency(fin);
    // space alloc
    stack = calloc(num_active - 1, sizeof(int));
    allocate_tree();

    add_leaves();
    write_header(fout);
    build_tree();
    fseek(fin, 0, SEEK_SET);
    int c;
    while ((c = fgetc(fin)) != EOF) {
        encode_alphabet(fout, c);
    }
    flush_buffer(fout);
    free(stack);
    fclose(fin);
    fclose(fout);
    return 0;
}

void encode_alphabet(FILE *fout, int character) {
    int node_index;
    stack_top = 0;
    node_index = leaf_index[character + 1];
    while (node_index < num_nodes) {
        stack[stack_top++] = node_index % 2;
        node_index = parent_index[(node_index + 1) / 2];
    }
    while (--stack_top > - 1) {
        write_bit(fout, stack[stack_top]);
    }

}

