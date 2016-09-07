#include <iostream>

#ifndef LIST_NODE_H 
#define LIST_NODE_H

struct Base_Node;

struct List_Node
{
	Base_Node * node;
	List_Node * next;

	List_Node(Base_Node * _node) : node(_node), next(0) 
	{
		std::cout << "Construct List_Node" << std::endl;
	}

	~List_Node();
};

#endif