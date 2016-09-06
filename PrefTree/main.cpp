#include <iostream>
#include "Node.h"

//Node * insert(node *tree_head, )


Node* insert(Node* tree_head, vector<unsigned char> &phones) // вставка нового слова в дерево treeHead
{
	if( !tree_head ) 
	{
		Base_Node * treeHead = new Node();		
		
		phones_length = phones.size();
		
		for (int inx = 0; inx < phones_length - 1; inx++)
		{
			Base_Node * new_node = new Node();
			new_node.set(phones_length[i], false, false);
		}
		
		Base_Node * new_node = new Base_Node();
		new_node.set(word[wordLen - 1], true, true);

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




int main() {
	
  string line;
  
  std::ifstream dictionary ("dictionary.txt");
  
  if (dictionary.is_open())
  {
	  
	
	
    while ( dictionary.good() )
    {
		vector<unsigned char> phones;
		vector<unsigned char> word;
		
		getline (dictionary, line);		
		
		while(fscanf(line, "%c", &word[i]))
		short int i = 0;
		bool isPhone = false;
	  
		while ( (i == 0) || (word[i-1] != ('\n')) )
		{		
			fscanf(line, "%c", &word[i]); // массив, содержащий фонемы очередного слова
        
			if (isPhone)
			{
				i++;
			}
			
			if (mas[i] == ('=')
			{
				isPhone = true;
			}     

		}
		
		
			
        if (word[i-1] == ('\n')) {
            break;
        }
	  
      cout << line << endl;
    }
    myfile.close();
  }

  else cout << "Unable to open file";

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