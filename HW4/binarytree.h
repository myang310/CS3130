// Ming Yang

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "node.h"

class BinaryTree {
	public:
		BinaryTree();
		~BinaryTree();
		void insert(int value, Node* current = root);
		bool delete(int value, Node* current = root);
		int count();
		void children();
		void inorder();
		void preorder();
		void postorder();

	private: 
		Node root;
		void destroy_tree(Node* leaf);
};

#endif