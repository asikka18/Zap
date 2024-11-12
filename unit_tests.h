/*  unit_tests.h
 *  Armaan Sikka
 *  3/27/24
 *
 *  CS 15 Proj 3 - Zap
 *
 *  A testing file for the phaseOne functions that uses the unit_test framework
 *
 */

#include <cassert>
#include <iostream>
#include <sstream>
#include "phaseOne.h"
#include "HuffmanTreeNode.h"
#include "ZapUtil.h"

using namespace std;

void test() {
    HuffmanTreeNode *tree = makeFigure1Tree('\0');
    string serial = serialize_tree(tree);
    assert(serial == "IIILaLbILeLfILcLd");
    cout << serial << endl;
    HuffmanTreeNode *root = deserialize_tree(serial);
    assert(serialize_tree(root) == serialize_tree(tree));
}
