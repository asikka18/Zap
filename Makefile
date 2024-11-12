###
### Makefile for Zap Project
###
### Author:  Armaan Sikka

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

minpq_example.o: HuffmanTreeNode.h minpq_example.cpp
	$(CXX) $(CXXFLAGS) -c minpq_example.cpp

ZapUtilExample.o: HuffmanTreeNode.o ZapUtilExample.o ZapUtil.o
	$(CXX) $(CXXFLAGS) -c ZapUtilExample.cpp

minpq_example: minpq_example.o HuffmanTreeNode.o
	$(CXX) $(CXXFLAGS) -o minpq_example minpq_example.o HuffmanTreeNode.o

ZapUtilExample: HuffmanTreeNode.o ZapUtilExample.o ZapUtil.o
	$(CXX) $(CXXFLAGS) -o ZapUtilExample HuffmanTreeNode.o ZapUtilExample.o ZapUtil.o

phaseOne.o: phaseOne.h phaseOne.cpp HuffmanTreeNode.o
	$(CXX) $(CXXFLAGS) phaseOne.cpp -c

unit_test: unit_test_driver.o phaseOne.o HuffmanTreeNode.o ZapUtil.o
	$(CXX) $(CXXFLAGS) unit_test_driver.o phaseOne.o HuffmanTreeNode.o ZapUtil.o

HuffmanCoder.o: HuffmanCoder.h HuffmanCoder.cpp HuffmanTreeNode.h BinaryIO.h
	$(CXX) $(CXXFLAGS) -c HuffmanCoder.cpp

main.o: main.cpp HuffmanCoder.h HuffmanTreeNode.h BinaryIO.h
	$(CXX) $(CXXFLAGS) -c main.cpp

zap: main.cpp HuffmanCoder.o HuffmanTreeNode.o BinaryIO.o
	$(CXX) $(CXXFLAGS) -o zap main.cpp HuffmanCoder.o HuffmanTreeNode.o BinaryIO.o

##
## Here is a special rule that removes all .o files besides the provided ones 
## (ZapUtil.o, HuffmanTreeNode.o, and BinaryIO.o), all temporary files 
## (ending with ~), and a.out produced by running unit_test. First, we find
## all .o files that are not provided files, then we run rm -f on each found
## file using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
		-name '*.o' ! -name 'HuffmanTreeNode.o' ! -name 'BinaryIO.o' \
		! -name 'ZapUtil.o' \) -exec rm -f {} \;
	@rm -f *~ a.out

