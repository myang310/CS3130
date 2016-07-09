// Ming Yang

#include "binarytree.h"
#include <iostream>
#include <cstdlib>
#include "node.h"

BinaryTree::BinaryTree() {
	root = NULL;
}

BinaryTree::~BinaryTree() {
	destroy_tree(root);
}

// Default functions as a workaround for default variables
// to be possible
void 
BinaryTree::insert(int value) {
	insert(value, root);
}

bool 
BinaryTree::remove(int value) {
	return remove(value, root);
}

int
BinaryTree::count() {
	return count(root);
}

void
BinaryTree::children() {
	children(root);
}

void
BinaryTree::inorder() {
	inorder(root);
}

void
BinaryTree::preorder() {
	preorder(root);
}

void
BinaryTree::postorder() {
	postorder(root);
}

void
BinaryTree::destroy_tree(Node*& leaf) {
	if (leaf != NULL) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
		leaf = NULL;
	}
}

// Actual functions with completed logic
void
BinaryTree::insert(int value, Node*& current) {
	// Look for the correct position to insert the integer
	if (current == NULL) 
		current = new Node(value);
	else if (value < current->data)
		insert(value, current->left);
	else 
		insert(value, current->right);
}

bool
BinaryTree::remove(int value, Node*& current) {
	if (current == NULL) 
		return false;

	// Proceed with the deletion process if the value is found
	if (value == current->data) {
		// Find the number of children of current node
		int children_count = 0;
		if (current->left != NULL) children_count++;
		if (current->right != NULL) children_count++;

		// Delete current node if no left or right child
		if (children_count == 0) {
			delete current;
			current = NULL;
			return true;
		}
		// Replace current node's data with right node if 2 children
		// Recursively call delete on the right node
		else if (children_count == 2) {
			current->data = current->right->data;
			return remove(current->right->data, current->right);
		}
		else {
			// Check which child exists and replace the parent with
			// the child node's data; recursively call delete on the child
			if (current->right == NULL) {
				Node* temp = current;
				current = current->left;
				delete temp;
				return true;
			}else {
				Node* temp = current;
				current = current->right;
				delete temp;
				return true;
			}
		}
	}
	// Otherwise search through the tree for the value
	else if (value < current->data) {
		return remove(value, current->left);
	}else {
		return remove(value, current->right);
	}
}

int
BinaryTree::count(Node*& leaf) {
	// Recursively figure out how many nodes in total in the BST
	if (leaf == NULL)
		return 0;
	else 
		return 1 + count(leaf->left) + count(leaf->right);
}

// Prints out the number of children each node has in the BST
void
BinaryTree::children(Node*& leaf) {
	if (leaf == NULL) return;

	children(leaf->left);

	int count = 0;
	if (leaf->left != NULL) count++;
	if (leaf->right != NULL) count++;
	std::cout << "Node: " << leaf->data << " has " << count 
		<< " children" << std::endl;

	children(leaf->right);
}
		
// Prints the entire BST inorder
void
BinaryTree::inorder(Node*& leaf) {
	if (leaf == NULL) return;
	
	inorder(leaf->left);
	std::cout << std::to_string(leaf->data) << " ";
	inorder(leaf->right);
}

// Prints the entire BST preorder
void
BinaryTree::preorder(Node*& leaf) {
	if (leaf == NULL) return;

	std::cout << std::to_string(leaf->data) << " ";
	preorder(leaf->left);
	preorder(leaf->right);
}
		
// Prints the entire BST postorder
void
BinaryTree::postorder(Node*& leaf) {
	if (leaf == NULL) return;

	postorder(leaf->left);
	postorder(leaf->right);
	std::cout << std::to_string(leaf->data) << " ";
}