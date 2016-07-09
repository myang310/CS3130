// Ming Yang

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "node.h"

class BinaryTree {
	public:
		BinaryTree();
		~BinaryTree();
		void insert(int value);
		bool remove(int value);
		int count();
		void children();
		void inorder();
		void preorder();
		void postorder();

	private: 
		Node* root;
		void destroy_tree(Node*& leaf);
		void insert(int value, Node*& current);
		bool remove(int value, Node*& current);
		int count(Node*& leaf);
		void children(Node*& leaf);
		void inorder(Node*& leaf);
		void preorder(Node*& leaf);
		void postorder(Node*& leaf);
};

#endif