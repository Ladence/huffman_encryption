//
// Created by Ladence on 01.04.2018.
//
#include <stdio.h>
#include "decode.h"
#include "../encoding/encode.h"
#include "../data_structure/treebuilder.h"
#include "../data_structure/datastructure.h"
#include "../bits_io/iobits.h"

int decode(const char *ifile, const char *ofile) {
    FILE *fin, *fout;
    if ((fin = fopen(ifile, "rb")) == NULL) {
        perror("Failed to open input file!");
        return FILE_OPEN_FAIL;
    }
    if ((fout = fopen(ofile, "wb")) == NULL) {
        perror("Failed to open output file!");
        return FILE_OPEN_FAIL;
    }
    if (read_header(fin) == 0) {
        build_tree();
        decode_bit_stream(fin, fout);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}

void decode_bit_stream(FILE *fin, FILE *fout) {
    int i = 0, bit, node_index = nodes[num_nodes].index;
    while (1) {
        bit = read_bit(fin);
        if (bit == -1) {
            break;
        }
        node_index = nodes[node_index * 2 - bit].index;
        if (node_index < 0) {
            char c = -node_index - 1;
            fwrite(&c, 1, 1, fout);
            if (++i == original_size) {
                break;
            }
            node_index = nodes[num_nodes].index;
        }
    }
}
