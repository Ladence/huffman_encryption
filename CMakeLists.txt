cmake_minimum_required(VERSION 3.8)
project(huff)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c data_structure/datastructure.c data_structure/treebuilder.c data_structure/datastructure.h encoding/encode.c encoding/encode.h data_structure/treebuilder.h decoding/decode.c decoding/decode.h bits_io/iobits.c bits_io/iobits.h)
add_executable(huff ${SOURCE_FILES})