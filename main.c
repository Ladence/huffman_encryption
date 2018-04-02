#include <stdio.h>
#include "data_structure/datastructure.h"
#include "encoding/encode.h"
#include "decoding/decode.h"
#include "bits_io/iobits.h"

#define FAILURE (-5)

typedef unsigned long long ull;

ull rdtsc();
void print_help();

int main(int argc, char **argv) {
    if (argc != 4) {
        print_help();
        return FAILURE;
    }
    init();
    ull firstPointTime, secondPointTime;

    if (strcmp(argv[1], "encode") == 0) {
        firstPointTime = rdtsc();
        encode(argv[2], argv[3]);
        secondPointTime = rdtsc();
        printf("Time : %llu ns", secondPointTime - firstPointTime);
    } else if (strcmp(argv[1], "decode") == 0) {
        firstPointTime = rdtsc();
        decode(argv[2], argv[3]);
        secondPointTime = rdtsc();
        printf("Time : %llu ns", secondPointTime - firstPointTime);
    } else {
        print_help();
    }
    finalize();
    return SUCCESS;
}

void print_help() {
    fprintf(stderr, "USAGE ./huffman [encode/decode] <in> <out>");
}

inline ull rdtsc() {
    unsigned int lo, hi;
    asm volatile ( "rdtsc\n" : "=a" (lo), "=d" (hi) );
    return ((ull)hi << 32) | lo;
}