#include <iostream>
#include <queue>
#include <limits>
#include <string>
#include <vector>

#include "HuffmanEncoding.h"

Node *create_node(char letter, int freq) {
  return new Node(letter, freq);
}

//Utility function
void traverse_util(Node *root, const std::string &sequence) {
  if (root->left == nullptr && root->right == nullptr) {
    std::cout << root->letter << " : " << sequence << std::endl;
    return;
  }

  if (root->left != nullptr) {
    traverse_util(root->left, sequence + "0");
  }

  if (root->right != nullptr) {
    traverse_util(root->right, sequence + "1");
  }
}

// Function to start the tree traversal
void traverse(Node *root) {
  traverse_util(root, "");
}