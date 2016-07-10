// Ming Yang

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "bubble.h"
#include "quick.h"
#include "heap.h"

void print_data(int arr[], int size);
void best(int b_value, int q_value, int h_value, std::string& winner);

int main() {
	std::ifstream inputFile; // Data file

	// Open input file
	inputFile.open("/home/myang310/Documents/CS3130/HW6/data");
	if(inputFile.fail()) {
		std::cout << "Cannot open inputFile";
		std::exit(1);
	}

	int size; // Size of the array to be read in
	std::string order; // Holds the heading describing the data

	while (inputFile.peek() != EOF) {
		inputFile >> size;
		inputFile >> order;

		// Print out the type of order the data is in
			if (order == "almost")
				std::cout << size << " numbers in almost sorted order" << std::endl;
			else if (order == "random")
				std::cout << size << " numbers in random order" << std::endl;
			else
				std::cout << size << " numbers in reverse order" << std::endl;

		int data[size]; // Array that data is read into

		// Read in data
		for (int i = 0; i < size; i++) {
			inputFile >> data[i];

			// Print out data as it is read in
			std::cout << std::setw(4) << data[i];
			if (i % 10 == 9)
				std::cout << std::endl;
		}
		std::cout << std::endl;

		// Copies of the original data to preserve the original order
		int bubble[size];
		int quick[size];
		int heap[size];
		for (int i = 0; i < size; i++)
			bubble[i] = quick[i] = heap[i] = data[i];

		// Variables to keep track of the number of comparisons and interchanges
		// within each sorting algorithm
		int bcomparisons = 0,
		    binterchanges = 0,
		    qcomparisons = 0,
		    qinterchanges = 0,
		    hcomparisons = 0,
		    hinterchanges = 0;

		// Sort each array using their respective sorting algorithms
		Bubble::sort(bubble, size, bcomparisons, binterchanges);
		Quick::sort(quick, size, qcomparisons, qinterchanges);
		Heap::sort(heap, size, hcomparisons, hinterchanges);

		// Print out the results of each sorted array
		std::cout << "Bubble Sort" << std::endl;
		print_data(bubble, size);
		std::cout << "Comparisons: " << bcomparisons << std::endl;
		std::cout << "Interchanges: " << binterchanges << std::endl;
		std::cout << std::endl;

		std::cout << "Quick Sort" << std::endl;
		print_data(quick, size);
		std::cout << "Comparisons: " << qcomparisons << std::endl;
		std::cout << "Interchanges: " << qinterchanges << std::endl;

		std::cout << std::endl;
		std::cout << "Heap Sort" << std::endl;
		print_data(heap, size);
		std::cout << "Comparisons: " << hcomparisons << std::endl;
		std::cout << "Interchanges: " << hinterchanges << std::endl;
		std::cout << std::endl;

		// Names of the best sorting algorithm for comparisons and interchanges
		std::string best_compar;
		std::string best_interch;
		best(bcomparisons, qcomparisons, hcomparisons, best_compar);
		best(binterchanges, qinterchanges, hinterchanges, best_interch);
		
		std::cout << "Least Comparisons: " << best_compar << std::endl;
		std::cout << "Least Interchanges: " << best_interch << std::endl;
		std::cout << "\n" << std::endl;
	}
}

void
print_data(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		std::cout << std::setw(4) << arr[i];
		if (i % 10 == 9)
			std::cout << std::endl;
	}
}

void
best(int b_value, int q_value, int h_value, std::string& winner) {
	if (b_value < q_value) {
		winner = "Bubble Sort";
		if (h_value < b_value)
			winner = "Heap Sort";
	}
	else {
		winner = "Quick Sort";
		if (h_value < q_value)
			winner = "Heap Sort";
	}
}