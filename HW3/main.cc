// Ming Yang

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <string>
#include <math.h>
#include "linkedlist.h"

std::string to_string(double, std::size_t);

int main() {
	std::ifstream inputFile; // data file
	
	// Open input file
	inputFile.open("/home/myang310/Documents/CS3130/HW3/data");
	if (inputFile.fail()) {
		std::cout << "Cannot open inputFile";
		std::exit(1);
	}
	
	LinkedList stock;
	char type = '\0';
	int amount = 0;
	double price = 0;
	double discount = 0;
	int discounts_left = 0;

	// Format output to print two decimal places
	std::cout << std::fixed << std::showpoint;
	std::cout << std::setprecision(2);

	// Read in data until the end
	while (inputFile >> type) {
		inputFile >> amount;

		if (type == 'R') {
			inputFile >> price;
			
			// Store the inventory in the list
			stock.push_back(amount, price);

			// Print receipt message
			std::cout << "Received " << amount << " at $" 
			<< price << " each\n" << std::endl;
		}

		else if (type == 'P') {
			char discard;
			inputFile >> discard; // removes '%'

			// Set up discounts
			discounts_left = 2;
			discount = amount / 100.0;

			// Print discount message
			std::cout << "Discount of " << amount 
				<< "% applied to the next two orders\n" << std::endl;
		}

		// Process the orders depending on availability
		else {
			int supply, // quantity that's in stock
			    total_sold = 0; // actual quantity sold
			double supply_price, // price of the stock 
			       total_price = 0; // total cost of the entire order
			int amount_needed = amount; // amount remaining to complete order
			bool discounted = false;
			std::string transaction_log = ""; // log of amounts sold and prices

			// Set up any available discounts
			if (discounts_left > 0) {
				discounted = true;
				discounts_left--;
			}

			// Keep popping from list until the order is fulfilled or
			// stock runs out
			while (amount_needed > 0 && !stock.is_empty()) {
				stock.pop_front(supply, supply_price);
				
				// price per unit after markup & discount
				double markup_price = supply_price * 1.3;

				// Apply any available discounts
				if (discounted)
					markup_price = markup_price * (1 - discount);

				if (amount_needed >= supply) {
					// Update the quantity needed
					amount_needed -= supply;

					// Update the total cost & sold
					total_price += supply * markup_price;
					total_sold += supply;

					// Add to the transaction log
					transaction_log += std::to_string(supply);
					transaction_log += " at $";
					transaction_log += to_string(markup_price, 2);
					transaction_log += " each\t Sales: $";
					transaction_log += to_string(supply * markup_price, 2);
					transaction_log += "\n";
				}else {
					// Add to the transaction log
					transaction_log += std::to_string(amount_needed);
					transaction_log += " at $";
					transaction_log += to_string(markup_price, 2);
					transaction_log += " each\t Sales: $";
					transaction_log += to_string(amount_needed * markup_price, 2);
					transaction_log += "\n";

					// Update the total cost & sold
					total_price += amount_needed * markup_price;
					total_sold += amount_needed;

					// Place the remaining supply back into stock
					supply -= amount_needed;
					amount_needed = 0;
					stock.push_front(supply, supply_price);
				}	
			}

			// Print the sales message
			std::cout << std::to_string(total_sold) << " widgets sold" << std::endl;
			std::cout << transaction_log;
			std::cout << "\t\tTotal Sales: $" << to_string(total_price, 2)
				<< std::endl;
			
			// Print that the amount needed exceeded the total supply
			if (amount_needed > 0)
				std::cout << "remainder of " << amount_needed
					<< " widgets not available\n" << std::endl;
			// Print blank line to separate orders
			else
				std::cout << std::endl;
		}
	}

	// Print out remaining widgets in stock	
	if (!stock.is_empty())
		std::cout << "\nStock remaining:" << std::endl;

	while (!stock.is_empty()) {
		stock.pop_front(amount, price);	
		std::cout << amount << " at $" << to_string(price, 2)
			<< " each" << std::endl;
	} 
}		

std::string to_string(double val, std::size_t prec)
{
    std::ostringstream os;
    os << std::fixed << std::setprecision(prec) << val;
    return os.str();
}