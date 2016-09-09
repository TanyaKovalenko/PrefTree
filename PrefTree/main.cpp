#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map> 
#include "Node.h"
#include "Phone.h"

const short int PHONE_ALPHABET_SIZE = 59;

std::map<std::string, unsigned int> form_phone_alphabet ( std::string phone_file_pass )
{
	std::map<std::string, unsigned int> the_phone_alphabet;
	std::string line;  
	std::ifstream phone_file ( phone_file_pass );

	if ( phone_file.is_open() )
	{			
		unsigned int phone_id = 0;
		short int first_quote_pos;
		short int second_quote_pos;
		std::string phone;

		while ( phone_id < PHONE_ALPHABET_SIZE )
		{
			getline ( phone_file, line );
			first_quote_pos = line.find ( '"' );
			second_quote_pos = line.find ( '"', first_quote_pos + 1 );
						
			phone = line.substr ( first_quote_pos + 1, second_quote_pos - first_quote_pos - 1 );
						
			the_phone_alphabet.insert ( std::pair<std::string, unsigned int>(phone, phone_id) );

			phone_id++;

		}	
	}

	phone_file.close();

	return the_phone_alphabet;
}

inline Node * as_node(Base_Node * node)
{
	return dynamic_cast<Node *>(node);
}

void form_tree ( std::string dictionary_file_pass, std::map<std::string, unsigned int> &the_phone_alphabet )
{
	std::string line;  
	std::ifstream dictionary_file ( dictionary_file_pass );

	Base_Node * tree_head = new Node();

	if ( dictionary_file.is_open() )
	{			
		unsigned int phone_id = 0, word_id;
		short int pos1, pos2;
		std::vector<unsigned int> phones;
		std::string phones_str, phone;

		while (dictionary_file.good())
		{
			getline ( dictionary_file, line );

			if (!line[0])
				continue;

			phone = "";

			pos1 = line.find ( '=' );
			pos2 = line.find ( '#' );
			
			phones_str = line.substr ( pos1 + 1, pos2 - pos1 - 1 );

			for ( short int phones_str_inx = 0; phones_str_inx <= phones_str.size(); phones_str_inx++ )
			{
				if ( ( phones_str[phones_str_inx] == ' ' ) || ( phones_str_inx == phones_str.size() ) )
				{
					phones.push_back ( the_phone_alphabet.find(phone)->second );

					phone = "";					
				} 
				else
				{
					phone += phones_str[phones_str_inx];
				}							
			}

			word_id = atoi ( line.substr ( pos2 + 1, line.size() - pos2 - 1 ).c_str() );


			// add word in the tree

			Base_Node * node = tree_head;
			List_Node *node_to_compare;
			List_Node *child_node;
			List_Node *id_node;
			bool need_add = false;

			for ( short int phones_inx = 0; phones_inx < phones.size(); phones_inx++ )
			{
				// выполняем добавление новой фонемы в дерево
				if (need_add) 
				{
					Base_Node *new_node = new Node();
					new_node->set(phones[phones_inx], false, false);
					as_node(node)->children.push(new_node);
					node = new_node;
				}
				else
				{					
					child_node = as_node(node)->children.first; 
					
					if ((!child_node) || (child_node->node->is_id()))
					{
						need_add = true;

						Base_Node *new_node = new Node();
						new_node->set(phones[phones_inx], false, false);
						as_node(node)->children.push(new_node);					
						node = new_node;
					} 
					else 
					{
						while (child_node)
						{
							node_to_compare = child_node;										

							if ( phones[phones_inx] != node_to_compare->node->get() )
							{
								if (child_node->next)
								{
									child_node = child_node->next;
								} 
								else
								{
									need_add = true;

									Base_Node *new_node = new Node();
									new_node->set(phones[phones_inx], false, false);
									as_node(node)->children.push(new_node);					
									node = new_node;

									break;	
								}						
							}
							else
							{
								node = node_to_compare->node;

								break;
							}					
						}						
					}

				}
			} 

			Base_Node *new_id_node = new Node();
			new_id_node->set(word_id, true, false);
			as_node(node)->children.push(new_id_node);

			std::cout << new_id_node->get() << std::endl;

			phones.clear();
		}	
	}

	dictionary_file.close();

	return;
}



int main() {
	
	std::map<std::string, unsigned int> the_phone_alphabet = form_phone_alphabet ( "phone.txt" );
		
	//Base_Node * tree_head = new Node();	

	//tree_head = form_tree("dictionary.txt");

	form_tree ( "dictionary.txt", the_phone_alphabet );
 
  
	/*while(true) 
	{
			Node * node = new Node();
			node->phone_num = 5;

			Base_Node * child_node = new Base_Node();
			child_node->phone_num = 3;
			node->children.push(child_node);
								
			delete node;

	} */

	/*Base_Node * base_node = new Base_Node();

	base_node->set(57, true, true);

	std::cout << (int)base_node->get();*/

	int y;
	std::cin >> y;
	
	return 0;
}