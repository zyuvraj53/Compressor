#include <array>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

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

// TODO: I am not cleaning up the memory for the huffman tree, use cleanUp for the HuffmanTree cleaning

#include "HuffmanEncoding.h"

std::array<int, 128> getCount(const char *path) {

  std::array<int, 128> characters = {};
  std::fstream file;

  file.open(path, std::ios::in); // Open file in read mode
  if (file.is_open()) {
    std::string line;
    std::cout << "File openened successfully" << std::endl;
    while (getline(file, line)) { // getline function takes the stream, and the string
      for (char c : line) {
        //! This never enters the else block, as char only ranges from 0 to 127
        // if (c >= 0 && c < 128) { // Ensure character is in the valid ASCII range
        // characters[c]++;
        //} else {
        // std::cout << "Warning: Non-ASCII character found: " << c << std::endl;
        //}

        //^ Fixed: changed the std::array from char to int and casted to unsigned char

        characters[static_cast<unsigned char>(c)]++;
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

Node *makeTree(std::array<int, 128> characters) {

  // char *chars = {};
  std::vector<char> chars;
  // int *frequencies = {};
  std::vector<int> frequencies;
  //! The mistake is somewhere here in the loop
  //^ Fixed: Changes in getCount()

  for (int i = 0; i < 128; i++) {
    if (characters[i] > 0) {
      frequencies.push_back(characters[i]);
      chars.push_back(static_cast<char> (i));
    }
  }

  //! Errors: frequencies and chars not assigning values
  //^ Fixed: was using normal array assignment, rather should use push_back

  //% Read about static_cast in C++

  //~ used for explicit type conversion
  //~ Provides a more safer and controlled way to typecast than traditional C style typecasting

  //~ Checked at compile time

  //~ Can be used for:
  //~   1. From a derived class pointer to a base class pointer
  //~   2. For conversions to and from fundamental data types
  //~   3. Convert pointers or references up and down the inheritance hierarchy in object-oriented code, but it cannot cast across or between unrelated types

  //~ Downcasting should be done with dynamic_cast

  //% Read about dynamic_cast in C++

  HuffmanTree ht = createHuffmanTree(chars, frequencies, chars.size());
  Node *root = ht.top();

  return root;
}

void buildCodes_util(std::unordered_map<char, std::string> huffmanCodes, Node *root, const std::string &str) {
  if (!root)
    return;

  if (!root->left && !root->right) { // Leaf node
    huffmanCodes[root->letter] = str;
  }

  buildCodes_util(huffmanCodes, root->left, str + "0");
  buildCodes_util(huffmanCodes, root->right, str + "1");
}

std::unordered_map<char, std::string> buildCodes(Node *root) {
  std::unordered_map<char, std::string> huffmanCodes;
  const std::string str;

  buildCodes_util(huffmanCodes, root, str);

  return huffmanCodes;
}

void encode_file(std::unordered_map<char, std::string> codes, const char *in_path, const char *out_path) {

  std::fstream in_file;
  std::fstream out_file;
  in_file.open(in_path, std::ios::in);
  out_file.open(out_path, std::ios::out); // writing , app for appending

  if (in_file.is_open() && out_file.is_open()) {
    std::string line;
    while (getline(in_file, line)) {
      for (char c : line) {
        out_file << codes[c];
      }
    }
  }

  in_file.close();
  out_file.close();
}

void zip_file(const char *in_path, const char *out_path) {

  delete_content(out_path);

  std::array<int, 128> characters = getCount(in_path);

  Node *root = makeTree(characters);

  std::unordered_map<char, std::string> codes = buildCodes(root);

  encode_file(codes, in_path, out_path);
}