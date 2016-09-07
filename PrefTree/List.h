#include <iostream>
#include "List_Node.h"
#include "Base_Node.h"

#ifndef LIST_H 
#define LIST_H 

struct Base_Node;

struct List
{
	List_Node * first;
	List() : first(0) 
	{
		std::cout << "Construct List" << std::endl;
	}
	~List();
	void push(Base_Node * node);

};

#endif
