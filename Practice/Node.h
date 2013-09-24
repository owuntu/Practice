#ifndef __ATOMBULDER_NODE_H_
#define __ATOMBULDER_NODE_H_

class Node
{
private:
	int			_val;

public:
	Node *		_p;
	Node *		_left;
	Node *		_right;
	Node():
	_val(0), 
		_left(NULL), 
		_right(NULL),
		_p(NULL)
	{}

	Node(const int i_val):
	_val(i_val), 
		_left(NULL), 
		_right(NULL),
		_p(NULL){}

	void setValue(const int & i_val)
	{
		_val = i_val;
	}

	const int & getValue() const
	{
		return _val;
	}
};


#endif //__ATOMBULDER_NODE_H_