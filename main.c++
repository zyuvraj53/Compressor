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
  std::priority_queue<Node *, std::vector<Node *>, Compare> minHeap;

  for (int i = 0; i < num; i++) {
    minHeap.push(create_node(alphabets[i], frequencies[i]));
  }

  // Building the Huffman tree
  while (minHeap.size() > 1) {
    Node *left = minHeap.top();
    minHeap.pop();
    Node *right = minHeap.top();
    minHeap.pop();

    Node *joined_node = create_node('\0', left->freq + right->freq); // internal node
    joined_node->left = left;
    joined_node->right = right;

    minHeap.push(joined_node);
  }

  // Last node is the root
  Node *root = minHeap.top();

  traverse(root);

  //----------------------------------------------
  delete[] alphabets;
  delete[] frequencies;

  // Cleanup: Postorder
  std::queue<Node *> cleanupQueue;
  cleanupQueue.push(root);
  while (!cleanupQueue.empty()) {
    Node *current = cleanupQueue.front();
    cleanupQueue.pop();
    if (current->left != nullptr)
      cleanupQueue.push(current->left);
    if (current->right != nullptr)
      cleanupQueue.push(current->right);
    delete current;
  }

  return 0;
}
