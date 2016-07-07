// Ming Yang

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

class LinkedList {
	public:
		LinkedList();
		void push_front(int count, double price);
		void push_back(int count, double price);
		void pop_front(int& count, double& price);
		bool is_empty();
	private:
		Node* head;
		Node* tail;
};

#endif
