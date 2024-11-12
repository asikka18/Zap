#ifndef _HUFFMAN_CODER
#define _HUFFMAN_CODER

#include <string>
#include <fstream>
#include <utility>
#include <string>
#include <sstream>
#include <queue>
#include <map>
#include <iostream>
#include <stack>
#include <vector>
#include "HuffmanTreeNode.h"
#include "BinaryIO.h"

class HuffmanCoder {
public:
    void encoder(const std::string &inputFile, const std::string &outputFile);
    void decoder(const std::string &inputFile, const std::string &outputFile);

private:
    void inputOpenOrDie(std::ifstream &input, std::string filename);
    std::map<char, int> count_freqs(std::ifstream &input);
    HuffmanTreeNode* makeTree(std::map<char, int> frequencies);
    void traverseMakeTree(HuffmanTreeNode* node, const std::string& currentCode,
                                    std::map<char, std::string>& charEncodings);
    std::string traverseOutputTree(HuffmanTreeNode* node, std::string& 
                                                            theBinaryString);
    std::map<char, std::string> makeEncodings(HuffmanTreeNode* root);
    std::string binaryString(std::map<char, std::string> charEncodings,
                                                        std::ifstream& input);
    std::string serialize_tree(HuffmanTreeNode *root);
    HuffmanTreeNode* deserialize_tree(std::istream &s);
};

#endif