/*
 *  phaseOne.cpp
 *  Armaan Sikka
 *  3/27/24
 *
 *  CS 15 Proj 3 Zap
 *
 *  Function definitions of phaseOne functions.
 *
 */

#include "phaseOne.h"

/*
 * name: count_freqs
 * purpose: to take input from the istream passed to it as an argument and count
 *          the instances of each character present (including whitespace) and
 *          print to cout the different characters and their 0uencies.
 * arguments: an input stream
 * returns: none
 * effects: prints each different character and its 0uency in the input steam
 *          to cout
 */
void count_freqs(std::istream &text) {
    std::unordered_map<char, int> charFreqsMap;
    char c;

    while (text.get(c)) {
        charFreqsMap[c]++;
    }

    for (auto &charFreq : charFreqsMap) {
        std::cout << charFreq.first << ": " << charFreq.second << std::endl;
    }
}

/*
 * name: serialize_tree
 * purpose: to serialise the HuffmanTree in the way specified in the spec.
 * arguments: a pointer to the root node of the HuffmanTree
 * returns: a string of the serialised version of the tree
 * effects: none
 */
std::string serialize_tree(HuffmanTreeNode *root) {
    if (root == nullptr) {
        return "";
    }

    std::stringstream serial_str;
    std::stack<HuffmanTreeNode *> serStack;

    serStack.push(root);

    while (not serStack.empty()) {
        HuffmanTreeNode *curr = serStack.top();
        serStack.pop();

        if (curr->isLeaf()) {
            serial_str << "L" << curr->get_val();

        } else {
            serial_str << "I";
            
            if (curr->get_right() != nullptr) {
                serStack.push(curr->get_right());
            }
            if (curr->get_left() != nullptr) {
                serStack.push(curr->get_left());
            }
        }
    }
    return serial_str.str();
}

/*
 * name: desHelper
 * purpose: deserialises a string passed to the function in the arguments
 *          according to the specified serial_str procedure given in the spec
 * arguments: a serial_str string and a integer for the index
 * returns: a pointer to the root of the created HuffmanTree
 * effects: none
 */
HuffmanTreeNode *desHelper(std::istream &s) {

    char c;
    s.get(c);

    if (c == 'I') {
        HuffmanTreeNode *curr = new HuffmanTreeNode('\0', 0);
        curr->set_left(desHelper(s));
        curr->set_right(desHelper(s));

        return curr;

    }else if (c == 'L') {
        char val;
        s.get(val);
        HuffmanTreeNode *curr = new HuffmanTreeNode(val, 0);

        return curr;
    }
}

/*
 * name: deserialize_tree
 * purpose: call a helper function to recursively deserialize a given serialized
 *          string
 deserialises a string passed to the function in the arguments
 *          according to the specified serial_str procedure given in the spec
 * arguments: a serial_str string
 * returns: a pointer to the root of a HuffmanTree
 * effects: none
 */
HuffmanTreeNode *deserialize_tree(const std::string &s) {
    std::stringstream theString(s);
    return desHelper(theString);
}
