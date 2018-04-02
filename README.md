# System of file encryption using Huffman's code

## Usage.
  You can build it with
  ```
  make 
  ```
  if you're in current directory 
  
  
  After at, use
  ```
  ./huffman [encode/decode] {path to input file} {path to output file}
  ```
  
## Approach
   We shall encode the input data stream one byte at a time. First of all, we have to calculate the frequency of each of the alphabets by parsing input data stream completely.

### Encode:
   We are using data structure based on array named "Binary coding tree" in which we maintain ASCII code (as byte) and frequency of alphabet (as unsigned).
   Building of BCT is so cumbersome, so you can look it at Wikipedia (useful links are located below).
   Since byte decoding starts at the root and traverses left or right depending on the bit value, we must encode the bits to allow this.
   In header of output file we have to maintain info about our structure, so decoder can rebuild tree.
   Since we start encoding at the leaves moving towards the root, we cannot emit the bits directly. Instead, we use a stack to reverse the order of the bits.
   We first get the node index assigned to the alphabet. Then, we use the parent_index table to move up the tree, retrieving the new parent using the index stored in the internal nodes. The value of the bit to be emitted is simply encoded by whether the index assigned to the internal node is either odd or even. 

### Decode:
   First of all, we have to repair BCT from header info. After that we are starting to decode the bit-stream : we retrieve one bit at a time and start from top of the coding tree - ROOT.
   Depending on the bit value, we decide where to go relatively current node. (Simple binary tree traversal, but we consider only two values - 1 and 0).
   When we got a leaf, we can get a decoded value.

## Useful links
   
   [Wiki Huffman Code](https://en.wikipedia.org/wiki/Huffman_coding)

   [BCT](https://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/)

   [Huffman's Decoding](https://www.geeksforgeeks.org/huffman-decoding/)
