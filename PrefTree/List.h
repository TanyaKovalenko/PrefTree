#include <iostream>
#include "List_Node.h"

#ifndef LIST_H 
#define LIST_H 

struct Node;

struct List
{
	List_Node * first;
	List() : first(0) 
	{
		std::cout << "Construct List" << std::endl;
	}
	~List();
	void push(Node * node);

};

#endif
