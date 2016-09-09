#include <iostream>
#include "Base_Node.h"

Base_Node::Base_Node()
{
	//std::cout << "Construct Base_Node" << std::endl;
}

void Base_Node::set(unsigned int value, bool is_id, bool is_leaf)
{
	data = value;
	
	if (is_id)
	{
		data = data | 1073741824;
	}
	
	if (is_leaf)
	{
		data = data | 2147483648;
	}
}

unsigned int Base_Node::get() const
{
	return data & 1073741823;
}

bool Base_Node::is_id() const
{
	// ������� ��� � phone_num �������� �� ��, �������� �� ���� ������. 1 - ��, 0 - ���
	if (data & 1073741824)
	{
		return true;
	}
	return false;
}

bool Base_Node::is_leaf() const
{
	// ������� ��� � phone_num �������� �� ��, �������� �� ���� ������. 1 - ��, 0 - ���
	if (data & 2147483648)
	{
		return true;
	}
	return false;
}

Base_Node::~Base_Node()
{
	//std::cout << "Destruct Base_Node" << std::endl;
}