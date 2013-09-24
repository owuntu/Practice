#ifndef __ATOMBUILDER_BINARY_TREE_H_
#define __ATOMBUILDER_BINARY_TREE_H_

class Node;

class BinaryTree
{
public:
	Node *			_root;
	unsigned int	_height;
	BinaryTree():
		_root(NULL),
		_height(0)
		{}

// 	void Insert(Node * z);
// 	void Delete(Node * z);

// 	Node * Search(const int & i_val) const;
// 	Node * GetMinimum() const;
// 	Node * GetMaximum() const;
};


#endif //__ATOMBUILDER_BINARY_TREE_H_