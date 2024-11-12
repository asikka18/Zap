#ifndef __PHASEONE_H
#define __PHASEONE_H

#include <istream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <sstream>

#include "HuffmanTreeNode.h"

void count_freqs(std::istream &text);
std::string serialize_tree(HuffmanTreeNode *root);
HuffmanTreeNode *deserialize_tree(const std::string &s);
HuffmanTreeNode *desHelper(const std::string &s);

#endif