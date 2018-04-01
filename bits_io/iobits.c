//
// Created by Ladence on 01.04.2018.
//

#include <mem.h>
#include <stdlib.h>
#include "iobits.h"
#include "../data_structure/datastructure.h"
int bits_in_buffer = 0;
unsigned char buffer[MAX_BUFFER_SIZE] = {0};
int current_bit = 0;
int eof_input = 0;

int write_bit(FILE *fout, int bit) {
    if (bits_in_buffer == MAX_BUFFER_SIZE << 3) {
        size_t bytes_written = fwrite(buffer, 1, MAX_BUFFER_SIZE, fout);
        if (bytes_written < MAX_BUFFER_SIZE && ferror(fout)) {
            return INVALID_BIT_WRITE;
        }
        bits_in_buffer = 0;
        memset(buffer, 0, MAX_BUFFER_SIZE);
    }
    if (bit) {
        buffer[bits_in_buffer >> 3] |= (0x1 << (7 - bits_in_buffer % 8));
    }
    ++bits_in_buffer;
    return SUCCESS;
}

int flush_buffer(FILE *fout) {
    if (bits_in_buffer) {
        size_t bytes_written = fwrite(buffer, 1, (bits_in_buffer + 7 >> 3), fout);
        if (bytes_written < MAX_BUFFER_SIZE && ferror(fout)) {
            return INVALID_BIT_WRITE;
        }
        bits_in_buffer = 0;
    }
    return SUCCESS;
}

int read_bit(FILE *fin) {
    if (current_bit == bits_in_buffer) {
        if (eof_input) {
            return EOF;
        } else {
            size_t bytes_read = fread(buffer, 1, MAX_BUFFER_SIZE, fin);
            if (bytes_read < MAX_BUFFER_SIZE) {
                if (feof(fin)) {
                    eof_input = 1;
                }
            }
            bits_in_buffer = bytes_read << 3;
            current_bit = 0;
        }
    }
    if (bits_in_buffer == 0) {
        return EOF;
    }
    int bit = (buffer[current_bit >> 3] >> (7 - current_bit % 8)) & 0x1;
    ++current_bit;
    return bit;
}

int write_header(FILE *fin) {
    int i, j, byte = 0;
    int size = sizeof(unsigned int) + 1 + num_active * (1 + sizeof(int));
    unsigned int weight;
    char *buffer = (char *)calloc(size, 1);
    if (buffer == NULL) {
        return MEM_ALLOC_FAIL;
    }

    j = sizeof(int);
    while (j--) {
        buffer[byte++] = (original_size >> (j << 3)) & 0xff;
    }
    buffer[byte++] = (char)num_active;
    for (i = 1; i <= num_active; i++) {
        weight = nodes[i].weight;
        buffer[byte++] = (char) (-nodes[i].index - 1);
        j = sizeof(int);
        while (j--) {
            buffer[byte++] = (weight >> (j << 3)) & 0xff;
        }
    }
    fwrite(buffer, 1, size, fin);
    free(buffer);
    return 0;
}

int read_header(FILE *f) {
    int i, j, byte = 0, size;
    size_t bytes_read;
    unsigned char buff[4];

    bytes_read = fread(&buff, 1, sizeof(int), f);
    if (bytes_read < 1)
        return EOF;
    byte = 0;
    original_size = buff[byte++];
    while (byte < sizeof(int))
        original_size =
                (original_size << (1 << 3)) | buff[byte++];

    bytes_read = fread(&num_active, 1, 1, f);
    if (bytes_read < 1)
        return EOF;

    allocate_tree();

    size = num_active * (1 + sizeof(int));
    unsigned int weight;
    char *buffer = (char *) calloc(size, 1);
    if (buffer == NULL)
        return MEM_ALLOC_FAIL;
    fread(buffer, 1, size, f);
    byte = 0;
    for (i = 1; i <= num_active; ++i) {
        nodes[i].index = -(buffer[byte++] + 1);
        j = 0;
        weight = (unsigned char) buffer[byte++];
        while (++j < sizeof(int)) {
            weight = (weight << (1 << 3)) |
                     (unsigned char) buffer[byte++];
        }
        nodes[i].weight = weight;
    }
    num_nodes = (int) num_active;
    free(buffer);
    return 0;
}