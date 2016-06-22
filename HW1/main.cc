// Ming Yang

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "transaction.h"
#include "record.h"

int main() {
	const int MLIMIT = 10;	// maximum number of master records
	const int TLIMIT = 50;	// maximum number of transaction records
	int mCount = 0;	// current number of master records
	int tCount = 0;	// current number of transactions
	Record masterRecords[MLIMIT];	// records of each customer
	std::ifstream masterFile, transactionFile;	// files holding the data
	Transaction transactions[TLIMIT];	// all customers' transactions
	char* input = new char[20];	// c-string to store input from the files
	
	// Open the master file
	masterFile.open("/home/myang310/Documents/CS3130/HW1/masterfile");
	if (masterFile.fail()) {
		std::cout << "Cannot open masterFile";
		std::exit(1);
	}

	// Open the transaction file
	transactionFile.open("/home/myang310/Documents/CS3130/HW1/transactionfile");
	if (transactionFile.fail()) {
		std::cout << "Cannot open transactionFile";
		std::exit(2);
	}

	// Fill out each record with data from the master file
	for (int i = 0; masterFile.peek() != EOF && i < MLIMIT; i++) {
		masterFile >> masterRecords[i].customerNumber;
		
		// skip any whitespaces
		while (masterFile.peek() == ' ')
			masterFile.get();

		masterFile.read(input, 20);
		masterRecords[i].name = std::string(input);
		
		// skip any whitespaces
		while (masterFile.peek() == ' ')
			masterFile.get();

		masterFile >> masterRecords[i].balance;
		
		// skip any new lines
		if (masterFile.peek() == '\n') 
			masterFile.get();
		mCount++;
	}

	// Fill out each transaction with data from the transaction file
	for (int i = 0; transactionFile.peek() != EOF && i < TLIMIT; i++) {
		char type = transactionFile.get();
		
		// fill out the appropriate fields for a payment
		if (type == 'O') {
			transactions[i].payment = false;
			transactionFile >> transactions[i].customerNumber;
			transactionFile >> transactions[i].transactionNumber;
			
			// skip any whitespaces
			while (transactionFile.peek() == ' ')
				transactionFile.get();

			transactionFile.read(input, 20);
			transactions[i].itemName = std::string(input);
			transactionFile >> transactions[i].quantity;
			transactionFile >> transactions[i].cost;
		} 
		// fill out the appropriate fields for an order
		else if (type == 'P') {
			transactions[i].payment = true;
			transactionFile >> transactions[i].customerNumber;
			transactionFile >> transactions[i].transactionNumber;
			transactionFile >> transactions[i].paymentAmt;
		} 
		// if neither payment nor order, then print out error
		else {
			std::cout << "Error with input transaction file - neither order nor payment";
			std::exit(3);
		}
	
		// skip any new lines
		if (transactionFile.peek() == '\n') 
			transactionFile.get();
		tCount++;
	}

	// adjust settings so doubles print with 2 decimals
	std::cout << std::fixed;
	std::cout << std::setprecision(2);

	std::cout << mCount << " " << tCount << std::endl;

	// print out the updated invoice
	for (int i = 0; i < mCount; i++) {
		std::cout << std::setw(25) << std::left << masterRecords[i].name;
		std::cout << masterRecords[i].customerNumber << std::endl;
		std::cout << std::setw(30) << std:: right << "Previous Balance: $"
			<< masterRecords[i].balance << std::endl;

		// search for this customer's transactions and update master record
		for (int j = 0; j < tCount; j++) {
			if (masterRecords[i].customerNumber == transactions[j].customerNumber) {
				std::cout << "Transaction #: " << transactions[j].transactionNumber;
				
				// print the payment information and update the master record
				if (transactions[j].payment) {
					// shift 12 as that's 25 minus the length of "Payment"
					std::cout << std::setw(12) << std::right << "Payment";
					// shift 14 to make up the difference
					std::cout << std::setw(14) << "$" << transactions[j].paymentAmt 
						<< std::endl;;
					masterRecords[i].balance -= transactions[j].paymentAmt;
				} 

				// print the order information and update the master record
				else {
					std::cout << std::setw(25) << std::right << transactions[j].itemName;
					double total = transactions[j].quantity * transactions[j].cost;
					std::cout << "$" << total << std::endl;
					masterRecords[i].balance += total;
				}
			}
		}
	
		// print the balance due
		std::cout << std::setw(30) << "Balance Due: $"
			<< masterRecords[i].balance << "\n" << std::endl;
	}

	masterFile.close();
	transactionFile.close();
	return 0;
}
