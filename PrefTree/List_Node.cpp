#include <iostream>
#include "List_Node.h"
#include "Node.h"

List_Node::~List_Node() 
{
	delete this->node;
}