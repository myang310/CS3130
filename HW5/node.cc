// Ming Yang

#include "node.h"
#include <cstdlib>

Node::Node(std::string data) {
	this->data = data;
	left = NULL;
	right = NULL;
}