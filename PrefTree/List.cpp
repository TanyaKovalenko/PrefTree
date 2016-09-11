#include "Node.h"
#include <iostream>
#include "List.h"

List::~List() 
{
	if (first)
	{
		List_Node * next_list_node = first;

		while(next_list_node->next)
		{
			List_Node * temp_node = next_list_node->next;
			delete next_list_node;
			next_list_node = temp_node;
		}
		
		delete next_list_node; 
	}	
}

void List::push(Base_Node * node)
{	
	List_Node * list_node = new List_Node(node);

	if(!first) 
	{
		first = list_node;
		return;
	}
						
	List_Node * next_list_node = first;

	while(next_list_node->next)
	{
		next_list_node = next_list_node->next;
	}

	next_list_node->next = list_node; 
			
	return;
			
} // put node in the list
