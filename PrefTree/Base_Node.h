#ifndef BASE_NODE_H 
#define BASE_NODE_H 

struct Base_Node
{
	unsigned char date;

	void set(unsigned char value, bool is_id, bool is_leaf);
	unsigned char get() const;

	bool is_leaf() const;
	bool is_id() const;

	Base_Node();
	virtual ~Base_Node();
};

#endif