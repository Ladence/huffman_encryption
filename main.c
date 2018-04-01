#include <stdio.h>
#include "data_structure/datastructure.h"
#include "encoding/encode.h"
#include "decoding/decode.h"
#include "bits_io/iobits.h"

#define FAILURE (-5)

void print_help();

int main(int argc, char **argv) {
    if (argc != 4) {
        print_help();
        return FAILURE;
    }
    init();
    if (strcmp(argv[1], "encode") == 0) {
        encode(argv[2], argv[3]);
    } else if (strcmp(argv[1], "decode") == 0) {
        decode(argv[2], argv[3]);
    } else {
        print_help();
    }
    finalize();
    return SUCCESS;
}

void print_help() {
    fprintf(stderr, "USAGE ./huffman [encode/decode] <in> <out>");
}