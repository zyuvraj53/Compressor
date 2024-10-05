#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <unordered_map>

#include "HuffmanEncoding.h"

std::array<int, 128> getCount(const char *in_path);

void delete_content(const char *out_path);

Node *makeTree(std::array<char, 128> characters);

void buildCodes_util(std::unordered_map<char, std::string> huffmanCodes, Node* root,const std::string &str);

std::unordered_map<char, std::string> buildCodes(Node* root);

void encode_file(std::unordered_map<char, std::string> codes, const char* in_path, const char* out_path);


void zip_file(const char* in_path, const char* out_path);