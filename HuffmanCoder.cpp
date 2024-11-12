/*
 *  HuffmanCoder.cpp
 *  Armaan Sikka
 *  3/27/24
 *
 *  CS 15 Proj 3 Zap
 *
 *  Function definitions of HuffmanCoder class.
 *
 */

#include "HuffmanCoder.h"

void deleteTree(HuffmanTreeNode* node) {
    if (node == nullptr) {
        return;
    }

    deleteTree(node->get_left());
    deleteTree(node->get_right());

    delete node;
}

/*
 * name: encoder
 * purpose: compresses the text in inputFile and stores the result in an output
 *          file
 * arguments: an input file and an output file
 * returns: none
 * effects: none
 */
void HuffmanCoder::encoder
(const std::string &inputFile, const std::string &outputFile)
{
    std::ifstream input;
    inputOpenOrDie(input, inputFile);

    // Counting character frequencies in the given text.
    std::map<char, int> frequencies = count_freqs(input);

    // Building the Huffman tree.
    HuffmanTreeNode *root = makeTree(frequencies);

    // Using the tree to generate character encodings.
    std::map<char, std::string> charEncodings = makeEncodings(root);

    // Using the generated encodings to encode the given text in binary.
    inputOpenOrDie(input, inputFile);
    std::string theString = binaryString(charEncodings, input);

    // Serializing the Huffman tree.
    std::string serialization = serialize_tree(root);

    // Saving the serialized tree and encoded text in a file.
    BinaryIO io;
    io.writeFile(outputFile, serialization, theString);

    // Count the bits in the file.
    int totalBits = theString.size();


    std::cout << "Success! Encoded given text using ";
    std::cout << totalBits << " bits." << std::endl;

    deleteTree(root);
}

/*
 * name: decoder
 * purpose: decompresses the text in inputFile and stores the result in an
 *          output file
 * arguments: an input file and an output file
 * returns: none
 * effects: none
 */
void HuffmanCoder::decoder(const std::string &inputFile, 
                                                const std::string &outputFile) {
    std::ifstream input;
    inputOpenOrDie(input, inputFile);

    // Reading a zap file to get the serialized tree and encoded binary string.
    BinaryIO io;
    std::pair<std::string, std::string> thePair = io.readFile(inputFile);

    // Deserializing the tree.
    std::stringstream myString(thePair.first);
    HuffmanTreeNode* root = deserialize_tree(myString);

    // Using the tree to decode the binary string into ASCII text.
    // Saving the ASCII text to an output file.
    std::ofstream output;
    output.open(outputFile);
    std::string anotherString = traverseOutputTree(root, thePair.second);
    output << anotherString;

    deleteTree(root);
    return;
}

/*
 * name: traverseOutputTree
 * purpose: recursively traverses the tree to find the leaf node and outputs the
 *          leaf val to the outputFile
 * arguments: a HuffmanTreeNode, the binary string, the output stream
 * returns: none
 * effects: none
 */
std::string HuffmanCoder::traverseOutputTree(HuffmanTreeNode* node, 
                        std::string& theBinaryString) {

    int size = theBinaryString.size();
    int i = 0;
    HuffmanTreeNode* curr;
    std::string thisString;

    while (i < size) {
        curr = node;

        while (i < size and not curr->isLeaf()) {
            if (theBinaryString[i] == '0') {
                curr = curr->get_left();

            } else {
                curr = curr->get_right();
            }
            i++;
        }

        if (curr->isLeaf()) {
            thisString += curr->get_val();
        }
    }

    if (not curr->isLeaf()) {
        throw std::runtime_error("Encoding did not match Huffman tree.");
    }

    return thisString;
}

/*
 * name: deserialize_tree
 * purpose: deserialises a string passed to the function in the arguments
 *          according to the specified serial_str procedure given in the spec
 * arguments: a serial_str string and a integer for the index
 * returns: a pointer to the root of the created HuffmanTree
 * effects: none
 */
HuffmanTreeNode* HuffmanCoder::deserialize_tree(std::istream &s) {
    char c;
    s.get(c);

    if (c == 'I') {
        HuffmanTreeNode *curr = new HuffmanTreeNode('\0', 0);
        curr->set_left(deserialize_tree(s));
        curr->set_right(deserialize_tree(s));

        return curr;

    } else if (c == 'L') {
        char val;
        s.get(val);
        HuffmanTreeNode *curr = new HuffmanTreeNode(val, 0);

        return curr;
    }

    return nullptr;
}

/*
 * name: serialize_tree
 * purpose: to serialise the HuffmanTree in the way specified in the spec.
 * arguments: a pointer to the root node of the HuffmanTree
 * returns: a string of the serialised version of the tree
 * effects: none
 */
std::string HuffmanCoder::serialize_tree(HuffmanTreeNode *root) {
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
 * name: binaryString
 * purpose: takes a map of the chars and their binary strings and iterates over
 *          the original text file to create the final binary string
 * arguments: the map of the chars and their binary strings and the input file
 * returns: a string of the final binary string of the input file
 * effects: none
 */
std::string HuffmanCoder::binaryString(std::map<char, std::string> 
                                        charEncodings, std::ifstream& input) {
    char c;
    std::string result;
    
    while (input.get(c)) {
        auto pair = charEncodings.find(c);
        result += pair->second;
    }

    input.close();
    return result;
}

/*
 * name: makeEncodings
 * purpose: takes the tree and makes a map of the characters and their binary
 *          strings based on the HuffmanTree made earlier
 * arguments: a pointer to the root of the HuffmanTree
 * returns: a map data structure of the different characters and their binary
 *          strings
 * effects: none
 */
std::map<char, std::string> HuffmanCoder::makeEncodings(HuffmanTreeNode* root) {
    std::map<char, std::string> charEncodings;
    std::string the = "";
    traverseMakeTree(root, the, charEncodings);
    return charEncodings;
}

/*
 * name: traverseMakeTree
 * purpose: traverses through the tree and creates the binary string associated
 *          with each leaf/character
 * arguments: a pointer to a HuffmanTreeNode, a binary string, the map of the
 *            chars and their binary strings
 * returns: none
 * effects: none
 */
void HuffmanCoder::traverseMakeTree(HuffmanTreeNode* node, const std::string&
                    currentCode, std::map<char, std::string>& charEncodings) {

    if (node == nullptr) {
        return;
    }

    if (node->isLeaf()) {
        charEncodings[node->get_val()] = currentCode;
        return;
    }

    traverseMakeTree(node->get_left(), currentCode + '0', charEncodings);
    traverseMakeTree(node->get_right(), currentCode + '1', charEncodings);
}

/*
 * name: makeTree
 * purpose: makes a tree from the map data structure that contains the different
 *          characters and their frequencies from the input file specified
 * arguments: a map data structure of the different characters and frequencies
 * returns: a pointer to the root of the HuffmanTree
 * effects: none
 */
HuffmanTreeNode* HuffmanCoder::makeTree(std::map<char, int> frequencies) {
    char nullChar = '\0';
    HuffmanTreeNode* curr;
    HuffmanTreeNode* parent;
    HuffmanTreeNode* temp1;
    HuffmanTreeNode* temp2;

    std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, 
                                                        NodeComparator> my_pq;
    for (auto &charFreq : frequencies) {
        curr = new HuffmanTreeNode(charFreq.first, charFreq.second);
        my_pq.push(curr);
    }

    while (my_pq.size() > 1) {
        temp1 = my_pq.top();
        my_pq.pop();
        temp2 = my_pq.top();
        my_pq.pop();
        parent = new HuffmanTreeNode(nullChar, 
                                    (temp1->get_freq() + temp2->get_freq()));
        parent->set_left(temp2);
        parent->set_right(temp1);
        my_pq.push(parent);
    }

    return my_pq.top();
}

/*
 * name: inputOpenOrDie
 * purpose: To open the file given in the command line and check whether file is
 *          open
 * arguments: the input-file stream and the filename
 * returns: None
 * effects: exits program if file is not open
 */
void HuffmanCoder::inputOpenOrDie(std::ifstream &input, std::string filename) {
    input.open(filename);

    if (not input.is_open()) {
        throw std::runtime_error("Unable to open file " + filename);
    }

    return;
}

/*
 * name: count_freqs
 * purpose: to take input file and count the frequency of each character that
 *          appears in the file and store it in a map
 * arguments: an input file
 * returns: a map data structure of the different characters that appear in the
 *          file and their frequency
 * effects: none
 */
std::map<char, int> HuffmanCoder::count_freqs(std::ifstream &input) {
    std::map<char, int> charFreqsMap;
    char c;

    while (input.get(c)) {
        charFreqsMap[c]++;
    }

    input.close();
    return charFreqsMap;
}
