#include <iostream>

#ifndef LIST_NODE_H 
#define LIST_NODE_H

struct Base_Node;

// The list of the children of every ordinary node 
// consists of the objects that have type List_Node.
// Every such object contains a node and a pointer to the next child of the list.
struct List_Node
{
	Base_Node * node;
	List_Node * next;

	List_Node(Base_Node * _node) : node(_node), next(0) 
	{}

	~List_Node();
};

#endif