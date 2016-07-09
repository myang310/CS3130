// Ming Yang

#include "binarytree.h"
#include "node.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

int main() {
	std::ifstream inputFile; // data file

	// Open input file
	inputFile.open("/home/myang310/Documents/CS3130/HW4/data");
	if(inputFile.fail()) {
		std::cout << "Cannot open inputFile";
		std::exit(1);
	}

	BinaryTree* btree;

	while (inputFile.peek() != EOF) {
		int number; // variable that holds each number that is read in
		btree = new BinaryTree(); // binary tree to hold all numbers

		// Build the binary search tree
		inputFile >> number;
		while (number != -999) {
			btree->insert(number);
			inputFile >> number;
		}

		// Print the tree using "inorder," "preorder," and "postorder"
		std::cout << "PRE-ADJUSTMENTS" << std::endl;
		std::cout << "Inorder: ";
		btree->inorder();
		std::cout << "\nPreorder: ";
		btree->preorder();
		std::cout << "\nPostorder: ";
		btree->postorder();
		std::cout << std::endl;

		// Count the number of nodes and print
		int count = btree->count();
		std::cout << "Count: " << count << std::endl;

		// Count the number of children each node has and print
		btree->children(); // Recursively transverses the tree and prints

		std::string command; // request to insert or delete
		int value; // number to be inserted or deleted from tree
		inputFile >> command;
		while (command != "End") {
			inputFile >> value;

			if (command == "Delete") {
				if (!btree->remove(value))
					std::cout << value << " was not found" << std::endl;
			}
			else if (command == "Insert") 
				btree->insert(value);

			inputFile >> command;
		}

		// Print the tree using "inorder," "preorder," and "postorder"
		std::cout << "\nPOST-ADJUSTMENTS" << std::endl;
		std::cout << "Inorder: ";
		btree->inorder();
		std::cout << "\nPreorder: ";
		btree->preorder();
		std::cout << "\nPostorder: ";
		btree->postorder();
		std::cout << std::endl;

		// Count the number of nodes and print
		count = btree->count();
		std::cout << "Count: " << count << std::endl;

		// Count the number of children each node has and print
		btree->children(); // Recursively transverses the tree and prints
		std::cout << "\n" << std::endl;

		delete btree; // Free memory after a data set is finished processing
	}
}