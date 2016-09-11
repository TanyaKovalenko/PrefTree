#include "List.h"
#include "Base_Node.h"

#ifndef NODE_H 
#define NODE_H 

// This struct inherited from struct Base_Node and is used to create an an ordinary node,
// that contains it's value (phone value) and lisf of children.
struct Node : public Base_Node
{
	List children;

	Node();
	~Node();
};

#endif