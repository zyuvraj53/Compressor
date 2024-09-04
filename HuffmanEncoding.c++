#include <iostream>
#include <queue>
#include <limits>
#include <string>
#include <vector>

// Node structure for the Huffman tree
typedef struct Node {
  char letter;
  int freq;
  struct Node *left;
  struct Node *right;

  // Constructor for ease of node creation
  Node(char l, int f) : letter(l), freq(f), left(nullptr), right(nullptr) {}
} Node;

// Comparator class to use with the priority queue
struct Compare {
  bool operator()(Node *a, Node *b) {
    return a->freq > b->freq; // Min-heap based on frequency
  }
};

// Function to create a new node
Node *create_node(char letter, int freq) {
  return new Node(letter, freq);
}

// Function to traverse the Huffman tree and print the codes
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

int main() {
  std::cout << "Enter the number of alphabets: " << std::endl;
  int num = 0;
  std::cin >> num;

  char *alphabets = new char[num];
  int *frequencies = new int[num];

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

  std::cout << "Enter the alphabets: " << std::endl;
  for (int i = 0; i < num; i++) {
    std::cin >> alphabets[i];
  }

  std::cout << "Enter the frequencies: " << std::endl;
  for (int i = 0; i < num; i++) {
    std::cin >> frequencies[i];
  }

  // Priority queue (min-heap) to store the nodes of the Huffman tree
  std::priority_queue<Node *, std::vector<Node *>, Compare> minHeap;
  // Priority Queue in C++?

  // Insert all characters and their frequencies into the priority queue
  for (int i = 0; i < num; i++) {
    minHeap.push(create_node(alphabets[i], frequencies[i]));
  }

  // Build the Huffman tree
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

  // The remaining node is the root of the Huffman tree
  Node *root = minHeap.top();

  // Traverse the Huffman tree to print the codes
  traverse(root);

  //----------------------------------------------
  delete[] alphabets;
  delete[] frequencies;

  // Cleanup: Deallocate the nodes in the Huffman tree
  // This is a basic post-order traversal to delete nodes
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
