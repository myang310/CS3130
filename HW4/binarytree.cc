// Ming Yang

#include "binarytree.h"
#include <iostream>

BinaryTree::BinaryTree() {
	root = NULL;
}

BinaryTree::~BinaryTree() {
	destroy_tree();
}

void
BinaryTree::insert(int value, Node* current) {
	if (current == NULL) 
		current = new Node(value);
	else if (value < current->data)
		insert(value, current->left);
	else 
		insert(value, current->right);
}

bool 
BinaryTree::delete(int value, Node* current) {
	if (value == current->data)
		
	else if (value < current->data)
}

int
BinaryTree::count(Node leaf = root) {
	if (leaf == NULL)
		return 0;
	else 
		return 1 + count(leaf->left) + count(leaf->right);
}

void 
BinaryTree::children(Node leaf = root) {
	if (leaf == NULL) return;

	children(leaf->left);

	int count = 0;
	if (leaf->left != NULL) count++;
	if (leaf->right != NULL) count++;
	std::cout << "Node: " << std::to_string(leaf->data)
		<< " has " << std::to_string(count) << " children";

	children(leaf->right);
}
		
void 
BinaryTree::inorder(Node leaf = root) {
	if (leaf == NULL) return;
	
	inorder(leaf->left);
	std::cout << std::to_string(leaf->data) << " ";
	inorder(leaf->right);
}
		
void 
BinaryTree::preorder() {
	if (leaf == NULL) return;

	std::cout << std::to_string(leaf->data) << " ";
	preorder(leaf->left);
	preorder(leaf->right);
}
		
void 
BinaryTree::postorder() {
	if (leaf == NULL) return;

	postorder(leaf->left);
	postorder(leaf->right);
	std::cout << std::to_string(leaf->data) << " ";
}

void 
BinaryTree::destroy_tree(Node* leaf) {
	if (leaf != NULL) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}

}