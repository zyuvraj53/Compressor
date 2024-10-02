#include <array>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

//! For now I am only considering ASCII characters as the characters that will be read, so I will be taking a 128 byte char array, if someone wants to extend this to include other character sets, they should use a hashtable, as an array will be too long

// 1. Take a char array 128 byte long

//~ What I want to do is take a file, read a dword(or a buffer) worth of data at a time and make a count array for all the characters in the file

// 1. Read a file 1 dword (or bufferlength) at a time
// 2. Keep count of all the characters in the char array

//~ And then after I have the array, make a huffman tree of the whole character array

// 1. Make a Huffman Tree from the array
// 2. Store all the characters in another array just like the previous one

//~ After the huffman tree has been made, I will again read the whole file one dword at a time, and convert it to Huffman Codes and keep appending it to an output file

// 1. Read the file again 1 dword (or bufferlength) at a time
// 2. For each character append the Huffman Codes to a new file
// 3. The new file will be the Encoded File

#include "HuffmanEncoding.h"

std::array<char, 128> getCount(const char *path) {

  std::array<char, 128> characters = {};
  std::fstream file;

  file.open(path, std::ios::in); // Open file in read mode
  if (file.is_open()) {
    std::string line;
    while (getline(file, line)) { // getline function takes the stream, and the string
      for (char c : line) {
        if (c >= 0 && c < 128) { // Ensure character is in the valid ASCII range
          characters[c]++;
        } else {
          std::cout << "Warning: Non-ASCII character found: " << c << std::endl;
        }
      }
    }
    file.close(); // Close the file after reading
  } else {
    std::cerr << "Could not open file!" << std::endl;
  }

  return characters;
}

void delete_content(const char *path) {
  std::ofstream file(path, std::ios::trunc); // trunc mode empties the file

  if (file.is_open()) {
    std::cout << "File contents deleted successfully." << std::endl;
    file.close();
  } else {
    std::cerr << "Failed to open the file." << std::endl;
  }
}

Node *makeTree(std::array<char, 128> characters) {

  char *chars = {};
  int *frequencies = {};

  int counter = 0;
  for (int i = 0; i < 128; i++) {
    if (characters[i] > 0) {
      frequencies[counter] = characters[i];
      chars[counter] = i;
      counter++;
    }
  }

  HuffmanTree ht = createHuffmanTree(chars, frequencies, counter);
  Node *root = ht.top();
  return root;
}

void buildCodes_util(std::unordered_map<char, std::string> huffmanCodes, Node* root,const std::string &str) {
  if (!root)
    return;

  if (!root->left && !root->right) { // Leaf node
    huffmanCodes[root->letter] = str;
  }

  buildCodes_util(huffmanCodes, root->left, str + "0");
  buildCodes_util(huffmanCodes, root->right, str + "1");
}

std::unordered_map<char, std::string> buildCodes(Node* root){
  std::unordered_map<char, std::string> huffmanCodes;
  const std::string str;

  buildCodes_util(huffmanCodes, root, str);

  return huffmanCodes;
}

void encode_file(std::unordered_map<char, std::string> huffmanCodes, const char* path){

  delete_content(path);

}