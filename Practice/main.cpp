#include <crtdbg.h>
#include<iostream>

#if defined(_DEBUG) | defined(DEBUG)

#ifndef ATNew
#define ATNew new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif //ATNew
#else
#ifndef ATNew
#define ATNew new
#endif //ATNew
#endif // _DEBUG

#include "Node.h"
#include "BinaryTree.h"
using namespace std;

void InOrderTreeWalk(Node * i_root);
void PreOrderTreeWalk(Node * i_root);
Node * TreeSearch(Node * i_root, const int & i_value);
Node * TreeMinimum(Node * i_root);
Node * TreeMaximum(Node * i_root);
Node * TreeSucessor(Node * i_node);
Node * TreePredecessor(Node * i_node);
void TreeInsert(BinaryTree * T, Node * z);
bool TreeDelete(BinaryTree * T,Node * z);
void TreeDestroy(BinaryTree * T);

int main(int argc, char** argv)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	//_CrtSetBreakAlloc(143);
#endif
	int dataSet[11] = {2, 4, 3, 6, 7, 13, 9, 15, 17, 18, 20};
	int dataSet2[12] = {15, 6, 18, 3, 7, 17, 20, 2, 5, 13, 9, 4};
	BinaryTree aTree;
	for (int i=0; i<12; i++)
	{
		Node * n = ATNew Node(dataSet2[i]);
		TreeInsert(&aTree, n);
	}

	//InOrderTreeWalk(aTree._root);
	
	PreOrderTreeWalk(aTree._root);
	cout<<endl;
	cout<<"Tree Height is "<<aTree._height<<endl;

	Node * nz = TreeSearch(aTree._root, 3);

	TreeDelete(&aTree, nz);
	delete nz;
	cout<<endl;
	PreOrderTreeWalk(aTree._root);
	cout<<endl;
	TreeDestroy(&aTree);

#if defined(DEBUG) | defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif

	system("pause");

	return 0;
}


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
		cout<<i_root->getValue()<<"(";
		//cout<<endl;
		if(i_root->_left != NULL){
			cout<<" L(";
			PreOrderTreeWalk(i_root->_left);
			cout<<")";
		}

		if(i_root->_right != NULL){
			cout<<"R(";
			PreOrderTreeWalk(i_root->_right);
			cout<<") ";
		}

		cout<<")";
		//cout<<endl;
	}
}


Node * TreeSearch(Node * i_root, const int & i_value) 
{
	Node * x = i_root;
	while(x != NULL && i_value != x->getValue())
	{
		if(i_value < x->getValue())
			x = x->_left;
		else
			x = x->_right;
	}
	return x;
}

Node * TreeMaximum(Node * i_root)
{
	Node * x = i_root;
	while(x->_right != NULL)
		x = x->_right;
	return x;
}

Node * TreeMinimum(Node * i_root)
{
	Node * x = i_root;
	while(x->_left != NULL)
		x = x->_left;
	return x;
}

Node * TreeSucessor(Node * i_node)
{
	if(i_node->_right != NULL)
	{
		return TreeMinimum(i_node->_right);
	}

	Node * c = i_node;
	Node * p = i_node->_p;
	while(p != NULL && c == p->_right)
	{
		c = p;
		p = p->_p;
	}
	return p;
}

Node * TreePredecessor(Node * i_node)
{
	if(i_node->_left != NULL)
		return TreeMaximum(i_node->_left);

	Node * c = i_node;
	Node * p = i_node->_p;
	while(p != NULL && c == p->_left)
	{
		c = p;
		p = p->_p;
	}
	return p;
}

void TreeInsertRecursive(BinaryTree * T, Node * z)
{
	if(z == NULL) return;
	if(T->_root == NULL){
		T->_root = z;
		return;
	}else if(T->_root->getValue() > z->getValue())
	{
		BinaryTree * leftSubT = ATNew BinaryTree;
		leftSubT->_root = T->_root->_left;
		TreeInsertRecursive(leftSubT, z);
		delete leftSubT;
	}else
	{
		BinaryTree * rigthSubT = ATNew BinaryTree;
		rigthSubT->_root = T->_root->_right;
		TreeInsertRecursive(rigthSubT, z);
		delete rigthSubT;
	}
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

bool TransPlant(BinaryTree * T, Node * u, Node * v)
{
	if(u->_p == NULL)
		T->_root = v;
	else if(u == u->_p->_left)
		u->_p->_left = v;
	else
		u->_p->_right = v;
	if(v != NULL)
		v->_p = u->_p;
	return true;
}

bool TreeDelete(BinaryTree * T,Node * z)
{
	if(z == NULL) return false;
	cout<<"Deleting"<<z->getValue()<<endl;
	if (z->_left == NULL)
	{
		TransPlant(T, z, z->_right);
	}else if(z->_right == NULL)
	{
		TransPlant(T, z, z->_left);
	}else
	{
		Node * zSucc = TreeSucessor(z); //or zSucc = TreeMinimum(z->_right);
		if(zSucc->_p != z)
		{
			TransPlant(T, zSucc, zSucc->_right);
			zSucc->_right = z->_right;
			zSucc->_right->_p = zSucc;
		}
		TransPlant(T, z, zSucc);
		zSucc->_left = z->_left;
		zSucc->_left->_p = zSucc;
	}

	return true;
}

void TreeDestroy(BinaryTree * T)
{
	Node * z = T->_root;
	while(z != NULL)
	{
		TreeDelete(T, z);
		delete z;
		z = T->_root;
	}
}