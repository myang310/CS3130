// Ming Yang

#include "linkedlist.h"
#include <cstddef>

LinkedList::LinkedList() {
	head = NULL;
	tail = NULL;
}

void
LinkedList::push_front(int count, double price) {
	Node* new_node = new Node();
	new_node->transaction = new Transaction(count, price);
	new_node->next_node = head;

	if (head == NULL && tail == NULL) {
		tail = new_node;
		head = new_node;
	}else
		head = new_node;
}

void
LinkedList::push_back(int count, double price) {
	Node* new_node = new Node();
	new_node->transaction = new Transaction(count, price);
	new_node->next_node = NULL;

	if (head == NULL && tail == NULL) {
		head = new_node;
		tail = new_node;
	}else {
		tail->next_node = new_node;
		tail = new_node;
	}		
}

void
LinkedList::pop_front(int& count, double& price) {
	count = head->transaction->count;
	price = head->transaction->price;
	
	Node* next_node = head->next_node;
	if (head == tail) {
		delete head->transaction;
		delete head;
		head = tail = NULL;
	}else {
		delete head->transaction;
		delete head;
		head = next_node;
	}
}

bool
LinkedList::is_empty() {
	return head == NULL;
}
