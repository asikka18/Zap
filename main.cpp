/*
 *  main.cpp
 *  Armaan Sikka
 *  3/27/24
 *
 *  CS 15 Proj 3 Zap
 *
 *  Main function that controls the Zap program.
 *
 */

#include <iostream>
#include "HuffmanCoder.h"

using namespace std;

int main(int argc, char *argv[]) {

    string name = argv[1];

    if (argc < 4 or argc > 4) {
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile" << endl;
        exit(EXIT_FAILURE);

    } else if (name == "zap") {
        HuffmanCoder run;
        run.encoder(argv[2], argv[3]);

    } else if (name == "unzap") {
        HuffmanCoder run;
        run.decoder(argv[2], argv[3]);
    }

    return 0;
}
