// Ming Yang

#include "binarytree.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include "node.h"

BinaryTree::BinaryTree() {
	root = NULL;
}

BinaryTree::~BinaryTree() {
	destroy_tree(root);
}
void 
BinaryTree::trav() {
	trav(root);
}

void 
BinaryTree::trav(Node* current) {
	if (current != NULL) {
		std::cout << current->data << " ";
		trav(current->left);
		trav(current->right);
	}
}

// Insert nodes into the tree, placing the older child always on the right
void
BinaryTree::insert(std::string child, std::string parent) {
	// Look for the parent node
	Node* dad = search(parent);
	if (dad != NULL) {
		// Place the "older" child on the right
		if (dad->right == NULL)
			dad->right = new Node(child);
		// Younger child goes on the left
		else
			dad->left = new Node(child);
	}
	// When the parent does not exist, the child is the root of the tree
	else
		root = new Node(child);
}

Node*
BinaryTree::search(std::string name) {
	return search(name, root);
}

// Searching for father #1
std::string 
BinaryTree::father(std::string name) {
	Node* parent = parent_of(name, root);
	if (parent != NULL)
		return parent->data;
	else
		return "None";
}

// Search for children #2
void
BinaryTree::children_of(std::string name, 
						std::string& child_one, 
						std::string& child_two) {
	Node* parent = search(name, root);
	
	// Check if the parent exists first
	if (parent != NULL) {
		// Then check if the older child exists, if so update name
		Node* older_child = parent->right;

		if (older_child != NULL)
			child_one = older_child->data;
		else
			child_one = "None";

		// Do the same for the younger child
		Node* younger_child = parent->left;
		if (younger_child != NULL)
			child_two = younger_child->data;
		else
			child_two = "None";
	}
}

// Search for brother #3
std::string
BinaryTree::brother(std::string name) {
	Node* parent = parent_of(name);

	// Check if the parent exists first
	if (parent != NULL) {
		// The grandparent has to have two sons for there to be an uncle
		if (parent->left == NULL || parent->right == NULL)
			return "None";
		// Whomever does not have the same name as the father is the uncle
		else if (parent->left->data == name)
			return parent->right->data;
		else
			return parent->left->data;
	}
	else
		return "None";
}

// Search for oldest brother #4
std::string
BinaryTree::oldest_brother(std::string name) {
	// Find parent & determine who is the right child
	Node* parent = parent_of(name);

	// Check if the parent exists first
	if (parent != NULL) {
		// Make sure to check if the right child exists
		if (parent->right != NULL) {
			std::string older_brother = parent->right->data;
			if (older_brother == name)
				return "Himself";
			else
				return older_brother;
		}else {
			return "None";
		}
	}else {
		return "None";
	}
}

// Search for youngest brother #5
std::string
BinaryTree::youngest_brother(std::string name) {
	// Find parent & determine who is the left child
	Node* parent = parent_of(name);
	// Check if the parent exists first
	if (parent != NULL) {
		// Make sure to check if the left child exists
		if (parent->left != NULL) {
			std::string younger_brother = parent->left->data;
			if (younger_brother == name)
				return "Himself";
			else
				return younger_brother;
		}else {
			return "None";
		}
	}else {
		return "None";
	}
}

// Search for oldest son #6
std::string
BinaryTree::oldest_son(std::string name) {
	Node* parent = search(name);
	// Check if the parent exists first
	if (parent != NULL) {
		// Make sure to check if the right child exists first
		if (parent->right != NULL) {
			return parent->right->data;
		}else {
			return "None";
		}
	}else {
		return "None";
	}
}

// Search for youngest son #7
std::string
BinaryTree::youngest_son(std::string name) {
	Node* parent = search(name);
	// Check if the parent exists first
	if (parent != NULL) {
		// Make sure to check if the left child exists first
		if (parent->left != NULL) {
			return parent->left->data;
		}else {
			return "None";
		}
	}else {
		return "None";
	}
}

// Search for uncle #8
std::string
BinaryTree::uncle(std::string name) {
	Node* parent = parent_of(name);
	// Check if the parent exists first
	if (parent != NULL) {
		Node* grandparent = parent_of(parent->data);
		// Check if the grandparent exists as well
		if (grandparent != NULL) {
			// Whenever there's only one son of the grandfather, 
			// no uncles exist
			if (grandparent->left == NULL || grandparent->right == NULL)
				return "None";
			else {
				// The grandfather's son without the parent's name is the uncle
				if (grandparent->left == parent)
					return grandparent->right->data;
				else
					return grandparent->left->data;
			}
		}else {
			return "None";
		}
	}else {
		return "None";
	}

}

// Search for grandfather #9
std::string
BinaryTree::grandfather(std::string name) {
	Node* parent = parent_of(name);
	// Check if the parent exists first
	if (parent != NULL) {
		Node* grandparent = parent_of(parent->data);
		// Check if the grandparent exists as well
		if (grandparent != NULL)
			return grandparent->data;
		else
			return "None";
	}else {
		return "None";
	}
}

// Free memory from each node in the tree; called by destructor
void
BinaryTree::destroy_tree(Node*& leaf) {
	if (leaf != NULL) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
		leaf = NULL;
	}
}

// Finds and returns the Node* of the sought after person
Node*
BinaryTree::search(std::string name, Node*& current) {
	if (current == NULL)
		return NULL;
	else if (current->data == name)
		return current;
	else {
		// Return as soon as you find the person; check right side first
		Node* right_side = search(name, current->right);
		if (right_side != NULL) 		
			return right_side;

		Node* left_side = search(name, current->left);
		if (left_side != NULL)		 	
			return left_side;
		
		// Return NULL when neither side has the name being searched for
		return NULL;
	}
}

Node* 
BinaryTree::parent_of(std::string name) {
	return parent_of(name, root);
}

// Searches for the parent of the given child, returns as a Node*
Node*
BinaryTree::parent_of(std::string name, Node*& current) {
	// When there's no root, there can be no parent
	if (current == NULL)
		return NULL;

	// Base case where there are no children of the current node
	if (current->left == NULL && current->right == NULL)
		return NULL;

	// When the left node is NULL, check to see if the right node 
	// has the name being sought after. Otherwise, recursively search
	// through the right side's nodes to see if any of those children
	// has the name being searched for
	else if (current->left == NULL) {
		if (current->right->data == name)
			return current;
		else {
			Node* right_side = parent_of(name, current->right);
			if (right_side != NULL)
				return right_side;
			else
				return NULL;
		}
	}
	// Same logic applies for the left side when the right node is NULL
	else if (current->right == NULL) {
		if (current->left->data == name)
			return current;
		else {
			Node* left_side = parent_of(name, current->left);
			if (left_side != NULL)
				return left_side;
			else
				return NULL;
		}
	}
	// Otherwise, when both nodes exist, recursively check both left
	// and right sides
	else {
		if (current->left->data == name || current->right->data == name)
			return current;
		else {
			Node* right_side = parent_of(name, current->right);
			if (right_side != NULL)
				return right_side;
			Node* left_side = parent_of(name, current->left);
			if (left_side != NULL)
				return left_side;
			return NULL;
		}
	}
}