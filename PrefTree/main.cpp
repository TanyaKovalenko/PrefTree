#include <iostream>
#include "Node.h"

//Node * insert(node *tree_head, )

/*
Node* insert(node* treeHead, char** word, int wordLen = 0) // вставка нового слова в дерево treeHead
{
	if( !wordLen ) 
	{
		// ?
	}

	if( !treeHead ) 
	{
		phoneLen = strlen(word[inx]);
		node* treeHead = new node(word[inx], phoneLen);
		
		for (int inx = 0; inx < wordLen; inx++)
		{
			phoneLen = strlen(word[inx]);
			treeHead = new node(word[inx], phoneLen);
		}

		return treeHead;
	}

	int k = prefix(phone, phoneLen, treeHead->key, treeHead->len);
	
	if( k == 0 ) 
	{
		treeHead->next = insert(treeHead->next, phone, phoneLen);
	}
	else if( k < phoneLen )
	{
		if( k < treeHead->phoneLen ) // режем или нет?
		{
			split(treeHead, k);
		}
		
		t->link = insert(treeHead->link, phone + k, phoneLen - k);
	}

	return treeHead;
}
*/

int main() {
	

	/*while(true) 
	{
			Node * node = new Node();
			node->phone_num = 5;

			Base_Node * child_node = new Base_Node();
			child_node->phone_num = 3;
			node->children.push(child_node);
								
			delete node;

	} */

	Base_Node * base_node = new Base_Node();

	base_node->set(57, true, true);

	std::cout << (int)base_node->get();

	int y;
	std::cin >> y;
	
	return 0;
}