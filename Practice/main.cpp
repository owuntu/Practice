#include<iostream>
#include "Node.h"
#include "BinaryTree.h"
using namespace std;

void InOrderTreeWalk(Node * i_root)
{
	if(i_root != NULL){
		InOrderTreeWalk(i_root->_left);
		cout<<i_root->getValue()<<' ';
		InOrderTreeWalk(i_root->_right);
		//cout<<endl;
	}
}

void PreOrderTreeWalk(Node * i_root)
{
	if(i_root != NULL){
		cout<<i_root->getValue()<<' ';
		//cout<<endl;
		PreOrderTreeWalk(i_root->_left);
		PreOrderTreeWalk(i_root->_right);
		//cout<<endl;
	}
}


Node * TreeSearch(Node * i_root, const int & i_value) 
{
	Node * x = i_root;
	while(x != NULL && i_value != x->getValue())
	{
		if(i_value<x->getValue())
			x = x->_left;
		else
			x = x->_right;
	}
	return x;
}

Node * TreeMinimum(Node * i_root)
{
	Node * x = i_root;
	while(x->_right != NULL)
		x = x->_right;
	return x;
}

Node * TreeMaximum(Node * i_root)
{
	Node * x = i_root;
	while(x->_left != NULL)
		x = x->_left;
	return x;
}

void TreeInsert(BinaryTree * T, Node * z)
{
	Node * zp = NULL;
	Node * nIter = T->_root;
	unsigned int cH = 0;

	while(nIter != NULL)
	{
		zp = nIter;
		if(z->getValue() > nIter->getValue())
		{
			nIter = nIter->_right;
		}else{
			nIter = nIter->_left;
		}
		cH++;
	}

	z->_p = zp;
	if(zp == NULL)
		T->_root = z;
	else if(z->getValue() > zp->getValue())
		zp->_right = z;
	else
		zp->_left = z;

	cH++;
	if(cH > T->_height) 
		T->_height = cH;
}

void TreeDelete(BinaryTree * T,Node * z)
{

}

int main(int argc, char** argv)
{
	int dataSet[11] = {2, 4, 3, 6, 7, 13, 9, 15, 17, 18, 20};
	int dataSet2[11] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
	BinaryTree aTree;
	for (int i=0; i<11; i++)
	{
		Node * n = new Node(dataSet2[i]);
		TreeInsert(&aTree, n);
	}

	//InOrderTreeWalk(aTree._root);
	
	PreOrderTreeWalk(aTree._root);
	cout<<endl;
	cout<<"Tree Height is "<<aTree._height<<endl;
	
	system("pause");

	return 0;
}