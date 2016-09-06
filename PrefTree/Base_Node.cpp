#include <iostream>
#include "Base_Node.h"

Base_Node::Base_Node()
{
	std::cout << "Construct Base_Node" << std::endl;
}

void Base_Node::set(unsigned char value, bool is_id, bool is_leaf)
{
	date = value;
	
	if (is_id)
	{
		date = date | 64;
	}
	
	if (is_leaf)
	{
		date = date | 128;
	}
}

unsigned char Base_Node::get() const
{
	return date & 63;
}

bool Base_Node::is_id() const
{
	// ������� ��� � phone_num �������� �� ��, �������� �� ���� ������. 1 - ��, 0 - ���
	if (date & 64)
	{
		return true;
	}
	return false;
}

bool Base_Node::is_leaf() const
{
	// ������� ��� � phone_num �������� �� ��, �������� �� ���� ������. 1 - ��, 0 - ���
	if (date & 128)
	{
		return true;
	}
	return false;
}

Base_Node::~Base_Node()
{
	std::cout << "Destruct Base_Node" << std::endl;
}