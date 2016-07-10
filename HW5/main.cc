// Ming Yang

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "binarytree.h"

int main() {
	std::ifstream inputFile; // data file

	// Open input file
	inputFile.open("/home/myang310/Documents/CS3130/HW5/data");
	if(inputFile.fail()) {
		std::cout << "Cannot open inputFile";
		std::exit(1);
	}

	BinaryTree* family_tree; // tree holding every member of family

	while (inputFile.peek() != EOF) {
		family_tree = new BinaryTree(); // allocate memory for the tree
		std::queue<std::string> queue; // to keep track of the parents while reading in data
		std::string name; // name of individual being read in
		int num_children; // the number of children belonging to this individual

		// Read in names and number of children until the end is reached
		inputFile >> name;
		while (name != "END") {
			inputFile >> num_children;

			// Push the name as many times as the number of children
			// to keep track of who each individual's parent is
			for (int i = 0; i < num_children; i++)
				queue.push(name);

			// Check the front of the queue for the parent of this child
			std::string parent = queue.front();
			family_tree->insert(name,parent);
			// Only pop from queue when this child has an actual parent
			// Otherwise the queue.front() will show its own name
			if (name != parent)
				queue.pop();

			inputFile >> name;
		}

		// Receive person to ask questions about
		std::string person;
		inputFile >> person;
		while(person != "END") {
			// Gather answers
			std::string father = family_tree->father(person);
			std::string child_one;
			std::string child_two;
			family_tree->children_of(person, child_one, child_two);
			std::string brother = family_tree->brother(person);
			std::string oldest_brother = family_tree->oldest_brother(person);
			std::string youngest_brother = family_tree->youngest_brother(person);
			std::string oldest_son = family_tree->oldest_son(person);
			std::string youngest_son = family_tree->youngest_son(person);
			std::string uncle = family_tree->uncle(person);
			std::string grandfather = family_tree->grandfather(person);

			// Print answers
			std::cout << "Person: " << person << std::endl;
			std::cout << "1. Father: " << father << std::endl;
			std::cout << "2. Children: " << child_one << " " << child_two << std::endl;
			std::cout << "3. Brother: " << brother << std::endl;
			std::cout << "4: Oldest Brother: " << oldest_brother << std::endl;
			std::cout << "5: Youngest Brother: " << youngest_brother << std::endl;
			std::cout << "6. Oldest Child: " << oldest_son << std::endl;
			std::cout << "7. Youngest Child: " << youngest_son << std::endl;
			std::cout << "8. Uncle: " << uncle << std::endl;
			std::cout << "9. Grandfather: " << grandfather << std::endl;
			std::cout << std::endl;

			// Input new individual to look up
			inputFile >> person;
		}

		// Free up family_tree memory
			delete family_tree;

		// Remove white spaces and new lines
		while (inputFile.peek() == ' ' || inputFile.peek() == '\n')
			inputFile.get();
	}
}