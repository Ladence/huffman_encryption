//
// Created by Ladence on 01.04.2018.
//

#include <stdio.h>

#ifndef HUFF_IOBITS_H
#define HUFF_IOBITS_H

#define MAX_BUFFER_SIZE 256
#define INVALID_BIT_READ (-1)
#define INVALID_BIT_WRITE (-1)
#define SUCCESS 1
#define MEM_ALLOC_FAIL (-2)

extern unsigned char buffer[MAX_BUFFER_SIZE];
extern int bits_in_buffer;
extern int current_bit;
extern int eof_input;

//write
int write_bit(FILE *, int bit);
int flush_buffer(FILE *);

//read
int read_bit(FILE *);

//header i/o
int write_header(FILE *);
int read_header(FILE *);

#endif //HUFF_IOBITS_H
