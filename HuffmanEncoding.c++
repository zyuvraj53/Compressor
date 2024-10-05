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

HuffmanTree createHuffmanTree(std::vector<char> alphabets, std::vector<int> frequencies, int num){
  HuffmanTree minHeap;

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

  return minHeap;
}

void cleanUp(Node *root){

  //Postorder Cleanup
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
}