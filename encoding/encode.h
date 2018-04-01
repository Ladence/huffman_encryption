//
// Created by Ladence on 01.04.2018.
//

#ifndef HUFF_ENCODE_H
#define HUFF_ENCODE_H
#define FILE_OPEN_FAIL (-1)
extern int *stack;
extern int stack_top;

int encode(const char *, const char *);
void encode_alphabet(FILE *, int);

#endif //HUFF_ENCODE_H
