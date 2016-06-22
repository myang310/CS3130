// Ming Yang

#include "record.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <exception>

int findMaxInventory(Record[], const int, int, int);


int main() {
	const int CITYCNT = 5; // number of cities
	const int ITEMCNT = 3; // number of item types
	std::ifstream inputFile; // file holding the data
	Record warehouses[CITYCNT]; // record of the warehouses

	// Input the names of the cities
	warehouses[0].cityName = "New York";
	warehouses[1].cityName = "Los Angeles";
	warehouses[2].cityName = "Miami";
	warehouses[3].cityName = "Houston";
	warehouses[4].cityName = "Chicago";
	
	// Zero out all the initial inventory counts
	for (int i = 0; i < CITYCNT; i++)
		for (int j = 0; j < ITEMCNT; j++)
			warehouses[i].stock[j] = 0;

	// Open the input file
	inputFile.open("/home/myang310/Documents/CS3130/HW2/inputFile");
	if (inputFile.fail()) {
		std::cout << "Cannot open inputFile";
		std::exit(1);
	}

	// Read in the prices (once as price is static)
	for (int i = 0; i < ITEMCNT; i++) {
		while (inputFile.peek() != '$')
			inputFile.get();
		// Get rid of the '$'
		inputFile.get();

		inputFile >> Record::price[i]; 
	}

	// Remove intermediary new lines
	while (inputFile.peek() == '\n')
		inputFile.get();

	// Process one line of data
	while(inputFile.peek() != EOF) {
		bool error = false; // changes to true if neither 's'
								  // nor 'o' is given first
								  
		bool enoughInStock = true; // item can be found in one
										   // of the warehouses

		bool replaced = false; // item had to be sent from a 
		                       // different warehouse

		std::string replacementMessage = ""; // printed if needed

		int replacement = -1; // the index of the replacement
									 // if necessary, -1 if unnecessary

		char type; // either (s)hipment or (o)rder

		bool isOrder = true; // input is for an order

		double totalCost; // total cost of the order

		int count[ITEMCNT]; // holds the transaction amounts

		int i; // index of the current transaction

		inputFile >> type;
		// Print back out the type
		std::cout << type << " ";

		// Store the city to be worked on
		std::string cityName, restOfName;
		inputFile >> cityName;
		
		// Append the rest of the name if applicable
		inputFile >> restOfName;
		try {
			count[0] = std::stoll(restOfName);
		}catch(...) {
			inputFile >> count[0];
			cityName += " " + restOfName;
		}

		// Find the city's index
		for (int j = 0; j < CITYCNT; j++) {
			if (warehouses[j].cityName == cityName) {
				i = j;
				break;
			}
		}

		// Read in the amount for the rest of the transaction
		for (int j = 1; j < ITEMCNT; j++)
			inputFile >> count[j];

		// Adjust the current records depending on
		// if it's an order or shipment
		if (type == 's') {
			isOrder = false;
			for (int j = 0; j < ITEMCNT; j++)
				warehouses[i].stock[j] += count[j];
		}else if (type == 'o') {
			// Check if all parts of the order can be fulfilled
			for (int j = 0; j < ITEMCNT; j++) {
				int preOrderAmt = warehouses[i].stock[j]; 
				int postOrderAmt = preOrderAmt - count[j];
			
				// Check if the warehouse or any alternative warehouses
				// can fulfill the order
				if (postOrderAmt < 0) {	
					replacement = findMaxInventory(warehouses, CITYCNT, j, count[j]);
					if (replacement == -1)
						enoughInStock = false;
				}
			}

			// Go ahead and process the order & update records
			if (enoughInStock) {
				for (int j = 0; j < ITEMCNT; j++) {
					int preOrderAmt = warehouses[i].stock[j]; 
					int postOrderAmt = preOrderAmt - count[j];

					// Search for a replacement warehouse if
					// a certain item's quantity is insufficient
					if (postOrderAmt < 0) {
						replacement = findMaxInventory(warehouses, CITYCNT, j, count[j]);
						// Save the output as a string to be printed later
						if (replacementMessage != "")
							replacementMessage += "\n";
						// Saves what & where it was shipped from/to
						replacementMessage += std::to_string(count[j]) + " of item "
							+ std::to_string(j + 1) + " shipped from " 
							+ warehouses[replacement].cityName + " to "
							+ warehouses[i].cityName + "\n";
						
						// Saves the updated record of the replacement warehouse
						warehouses[replacement].stock[j] -= count[j];
						size_t fillerCnt = 27 - warehouses[replacement].cityName.size();
						replacementMessage += warehouses[replacement].cityName;
						replacementMessage.append(fillerCnt, ' ');
						for (int k = 0; k < ITEMCNT; k++)
							replacementMessage += std::to_string(warehouses[replacement].stock[k]) 
								+ " ";
	
						totalCost += count[j] * Record::price[j] * 1.1;
						replaced = true;
					}else {
						warehouses[i].stock[j] = postOrderAmt;
						totalCost += count[j] * Record::price[j];
					}
				}
			}
		
		// Move onto the next line
		while (inputFile.peek() == '\n')
			inputFile.get();
		}

		// Print out the rest of the line of data
		// read in
		std::cout << std::setw(25) << std::left
			<< warehouses[i].cityName;
		for (int j = 0; j < ITEMCNT; j++)
			std::cout << count[j] << " ";
		std::cout << std::endl;

		// Print out the updated record of the
		// replacement warehouse
		if (replaced)
			std::cout << replacementMessage << std::endl;
		

		// Print error message if insufficient stock
		if (!enoughInStock) 
			std::cout << "Order Unfilled" << std::endl;	

		// Print out the updated record of the main
		// warehouse		
		if (!error && enoughInStock) {
			std::cout << std::setw(27) << warehouses[i].cityName;
			for (int j = 0; j < ITEMCNT; j++)
				std::cout << warehouses[i].stock[j] << " "; 
			std::cout << std::endl;
		}

		if (isOrder && enoughInStock && !error) {
			// Format output of doubles to print only two
			// decimal points
			std::cout << std::fixed;
			std::cout << std::setprecision(2);
		
			// Print out the total order price
			std::cout << std::setw(12) << "Price of Order: $" 
				<< totalCost << std::endl;
		}

		std::cout << std::endl;
	}
}

// Function findMaxInventory
// Input:
//	  warehouses - the array of records to search through
//	  N - the number of warehouses
//   itemLookFor - the index of the item to compare
//   amtLookFor - the minimum amount required to not return -1
// Process: Finds the warehouse holding the maximum
// amount of an item. 
// Output: Returns the index of that
// warehouse if the amount is greater than or equal
// to the amount requested. Otherwise returns 0.
int
findMaxInventory (Record warehouses[], 
					   const int N,
					   int itemLookFor, 
					   int amtLookFor) {
	int indexOfMax = -1; // holds the index of the max
	int maxAmt = 0; // maximum amount of the item
	for (int i = 0; i < N; i++) {
		int stock = warehouses[i].stock[itemLookFor];
		if (stock > maxAmt) {
			maxAmt = stock;
			indexOfMax = i;
		}
	}
	if (maxAmt >= amtLookFor)	return indexOfMax;
	else								return -1;
}






















