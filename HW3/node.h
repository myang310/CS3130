// Ming Yang

#ifndef NODE_H
#define NODE_H

#include "transaction.h"

struct Node {
	Node* next_node;
	Transaction* transaction;	
};

#endif
