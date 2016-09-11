#ifndef BASE_NODE_H 
#define BASE_NODE_H 

// The tree of the phonems comprises Base_Node objects. 
// Every such object contains a data (phone value or id of the word).
// It (object) can be an ordinary node, that contains it's value and lisf of children (see struct Node)
// of a leaf node.
struct Base_Node
{
	unsigned int data;

	void set(unsigned int value, bool is_id, bool is_leaf);
	unsigned int get() const;

	bool is_leaf() const;
	bool is_id() const;

	Base_Node();
	virtual ~Base_Node();
};

#endif