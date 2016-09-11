#include <iostream>
#include <limits>
#include "Base_Node.h"

const unsigned int MAX_UNIT = std::numeric_limits<unsigned int>::max();
const unsigned int OR_LEAF_MASK = ( ( MAX_UNIT / 2 ) + 1 );
const unsigned int OR_ID_MASK = ( ( MAX_UNIT / 4 ) + 1 );
const unsigned int GET_MASK = ( OR_ID_MASK - 1 );

Base_Node::Base_Node()
{}

void Base_Node::set(unsigned int value, bool is_id, bool is_leaf)
{
	data = value;
	
	if (is_id)
	{
		data = data | OR_ID_MASK;
	}
	
	if (is_leaf)
	{
		data = data | OR_LEAF_MASK;
	}
}

unsigned int Base_Node::get() const
{
	return data & GET_MASK;
}

bool Base_Node::is_id() const
{
	// Significant bit in phone_num responsible for whether node is ID. 1 - yes , 0 - no
	if (data & OR_ID_MASK)
	{
		return true;
	}
	return false;
}

bool Base_Node::is_leaf() const
{
	// Significant bit in phone_num responsible for whether node is leaf. 1 - yes , 0 - no
	if (data & OR_LEAF_MASK)
	{
		return true;
	}
	return false;
}

Base_Node::~Base_Node()
{}