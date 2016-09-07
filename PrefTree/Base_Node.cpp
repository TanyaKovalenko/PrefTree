#include <iostream>
#include "Base_Node.h"

Base_Node::Base_Node()
{
	std::cout << "Construct Base_Node" << std::endl;
}

void Base_Node::set(unsigned int value, bool is_id, bool is_leaf)
{
	date = value;
	
	if (is_id)
	{
		date = date | 1073741824;
	}
	
	if (is_leaf)
	{
		date = date | 2147483648;
	}
}

unsigned int Base_Node::get() const
{
	return date & 1073741823;
}

bool Base_Node::is_id() const
{
	// ������� ��� � phone_num �������� �� ��, �������� �� ���� ������. 1 - ��, 0 - ���
	if (date & 1073741824)
	{
		return true;
	}
	return false;
}

bool Base_Node::is_leaf() const
{
	// ������� ��� � phone_num �������� �� ��, �������� �� ���� ������. 1 - ��, 0 - ���
	if (date & 2147483648)
	{
		return true;
	}
	return false;
}

Base_Node::~Base_Node()
{
	std::cout << "Destruct Base_Node" << std::endl;
}