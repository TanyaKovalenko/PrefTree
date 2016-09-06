#include "List.h"
#include "Base_Node.h"

#ifndef NODE_H 
#define NODE_H 

struct Node : public Base_Node
{
	List children;

	Node();
	~Node();
};

#endif