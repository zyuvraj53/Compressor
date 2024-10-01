#include <iostream>
#include <queue>
#include <limits>
#include <string>
#include <vector>

#include "HuffmanEncoding.h"

int main() {
  std::cout << "Enter the number of alphabets: " << std::endl;
  int num = 0;
  std::cin >> num;

  char *alphabets = new char[num];
  int *frequencies = new int[num];

  // For flushing the input stream
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

  std::cout << "Enter the alphabets: " << std::endl;
  for (int i = 0; i < num; i++) {
    std::cin >> alphabets[i];
  }

  std::cout << "Enter the frequencies: " << std::endl;
  for (int i = 0; i < num; i++) {
    std::cin >> frequencies[i];
  }

  // Priority queue (min-heap) for the tree

  HuffmanTree huffman_tree;

  huffman_tree = createHuffmanTree(alphabets, frequencies, num);

  // Last node is the root
  Node *root = huffman_tree.top();

  traverse(root);

  //----------------------------------------------
  delete[] alphabets;
  delete[] frequencies;

  cleanUp(root);

  return 0;
}
