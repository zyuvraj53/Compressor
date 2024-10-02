#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <unordered_map>

#include "HuffmanEncoding.h"

std::array<char, 128> getCount(const char *path);

void delete_content(const char *path);

Node *makeTree(std::array<char, 128> characters);

void buildCodes_util(std::unordered_map<char, std::string> huffmanCodes, Node* root,const std::string &str);

std::unordered_map<char, std::string> buildCodes(Node* root);

void zip_file(std::unordered_map<char, std::string> codes, const char* in_path, const char* out_path);


void encode_file(std::unordered_map<char, std::string> huffmanCodes, const char* in_path, const char* out_path);