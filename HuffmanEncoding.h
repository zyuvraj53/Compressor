#include <string>
typedef struct Node {
  char letter;
  int freq;
  struct Node *left;
  struct Node *right;

  Node(char l, int f) : letter(l), freq(f), left(nullptr), right(nullptr) {}
} Node;

struct Compare {
  // Overloading function call operator for making a Min-Heap
  bool operator()(Node *a, Node *b){
    return a->freq > b->freq; // Min-heap based on frequency
  }
};

// Making a custom priority queue
// Stores Node*
// Uses vector to store Node *
// Uses a custom Compare struct to compare the frequencies in the Node*
typedef std::priority_queue<Node *, std::vector<Node *>, Compare> HuffmanTree;

Node *create_node(char letter, int freq);

//Utility function
void traverse_util(Node *root, const std::string &sequence);

// Function to start the tree traversal
void traverse(Node *root);

HuffmanTree createHuffmanTree(std::vector<char> alphabets, std::vector<int> frequencies, int num);

void cleanUp(Node *root);