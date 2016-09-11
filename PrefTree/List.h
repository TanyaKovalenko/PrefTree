#include <iostream>
#include "List_Node.h"
#include "Base_Node.h"

#ifndef LIST_H 
#define LIST_H 

struct Base_Node;

// The struct contains the list of the children of the every ordinary node.
struct List
{
	List_Node * first;
	List() : first(0) 
	{}
	~List();
	void push(Base_Node * node);

};

#endif
