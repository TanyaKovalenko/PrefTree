#ifndef BASE_NODE_H 
#define BASE_NODE_H 

struct Base_Node
{
	unsigned int date;

	void set(unsigned int value, bool is_id, bool is_leaf);
	unsigned int get() const;

	bool is_leaf() const;
	bool is_id() const;

	Base_Node();
	virtual ~Base_Node();
};

#endif