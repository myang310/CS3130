// Ming Yang

#ifndef TRANSACTION_H
#define TRANSACTION_H

struct Transaction {
	bool payment;
	std::string customerNumber;
	std::string transactionNumber;
	std::string itemName;
	double quantity;
	double cost;
	double paymentAmt;
};

#endif
