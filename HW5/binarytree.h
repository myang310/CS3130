// Ming Yang

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "node.h"
#include <vector>

class BinaryTree {
	public:
		BinaryTree();
		~BinaryTree();
		void trav();
		void trav(Node* current);
		void insert(std::string child, std::string parent);
		Node* search(std::string name);
		std::string father(std::string sname);
		void children_of(std::string parent,
						 std::string& child_one,
						 std::string& child_two);
		std::string brother(std::string name);
		std::string oldest_brother(std::string name);
		std::string youngest_brother(std::string name);
		std::string oldest_son(std::string name);
		std::string youngest_son(std::string name);
		std::string uncle(std::string name);
		std::string grandfather(std::string name);

	private: 
		Node* root;
		void destroy_tree(Node*& leaf);
		Node* search(std::string name, Node*& current);
		Node* parent_of(std::string name);
		Node* parent_of(std::string name, Node*& current);

};

#endif