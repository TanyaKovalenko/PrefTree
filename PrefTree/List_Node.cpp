#include <iostream>
#include "List_Node.h"
#include "Node.h"

List_Node::~List_Node() 
{
	//std::cout << "Destruct List_Node" << std::endl;
	delete this->node;
}