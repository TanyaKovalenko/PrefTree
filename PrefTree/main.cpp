#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <map> 
#include "Node.h"
#include "Phone.h"

const short int PHONE_ALPHABET_SIZE = 59;

std::pair < std::map <std::string, unsigned int>, 
			std::map < unsigned int, std::string > > form_phone_alphabet ( std::string phone_file_pass )
{
	std::map < std::string, unsigned int > the_phone_alphabet;
	std::map < unsigned int, std::string > the_reverse_phone_alphabet;
	std::string line;  
	std::ifstream phone_file;
	phone_file.open ( phone_file_pass.c_str() );

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
			the_reverse_phone_alphabet.insert ( std::pair<unsigned int, std::string>(phone_id, phone) );

			phone_id++;

		}	
	}

	phone_file.close();

	return std::make_pair ( the_phone_alphabet, the_reverse_phone_alphabet );
}

inline Node * as_node(Base_Node * node)
{
	return dynamic_cast<Node *>(node);
}

int get_id( Base_Node * tree_head, 
		    const std::vector < std::string > &phones,
			const std::map < std::string, unsigned int > & the_phone_alphabet )
{
	Base_Node * node = tree_head;
	List_Node * child_node;
	List_Node * node_to_compare;

	for (std::size_t phones_inx = 0; phones_inx <= phones.size(); phones_inx++ )
	{		
		child_node = as_node(node)->children.first;
					
		if (phones_inx == phones.size())
		{
			while (child_node)
			{
				if (child_node->node->is_id())
				{
					return child_node->node->get();
				} 
				if (child_node->next)
				{
					child_node = child_node->next;
				} 
				else
				{
					return 0;
				}
			}
		} 
		else 
		{
			if (child_node->node->is_id() && (phones_inx == phones.size()))
			{
				return child_node->node->get();
			} 
			else 
			{
				while (child_node)
				{
					node_to_compare = child_node;	

					if ( the_phone_alphabet.find(phones[phones_inx])->second != node_to_compare->node->get() )
					{
						if (child_node->next)
						{
							child_node = child_node->next;
						} 
						else
						{
							return 0;
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
}

Base_Node * form_tree ( Base_Node * tree_head, 
					    const std::string & dictionary_file_pass, 
						const std::map < std::string, unsigned int > & the_phone_alphabet )
{
	int node_count = 0;
	std::string line;  
	std::ifstream dictionary_file ( dictionary_file_pass.c_str() );

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

			for (std::size_t phones_str_inx = 0; phones_str_inx <= phones_str.size(); phones_str_inx++ )
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
			bool need_add = false;

			for ( std::size_t phones_inx = 0; phones_inx < phones.size(); phones_inx++ )
			{
				// выполняем добавление новой фонемы в дерево
				if (need_add) 
				{
					node_count++;
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
						node_count++;
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
									node_count++;
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
			node_count++;

			phones.clear();
		}	
	}

	dictionary_file.close();

	std::cout << "Count of the codes are " << node_count << std::endl;

	return tree_head;
}

void add_new_word_in_the_dictionary ( List_Node * child_node, 
									  std::vector<std::string> & phones, 
									  std::ofstream & result_dictionary_file,
									  const std::map<unsigned int, std::string> & the_reverse_phone_alphabet ) 
{
	if (child_node->node->is_id())
	{
		for ( unsigned int inx = 0; inx < phones.size(); inx++ )
		{
			result_dictionary_file << phones[inx];

			if (inx < phones.size() - 1) 
			{
				result_dictionary_file << " ";
			}

		}
		result_dictionary_file << "#" << child_node->node->get() << '\n';

		return;
	}	

	phones.push_back ( the_reverse_phone_alphabet.find ( child_node->node->get() )->second );

	child_node = as_node(child_node->node)->children.first; 

	while (child_node)
	{
		add_new_word_in_the_dictionary ( child_node, phones, result_dictionary_file, the_reverse_phone_alphabet );	
		child_node = child_node->next; 
	} 
	
	phones.pop_back();
	return;
}

void form_dictionary ( Base_Node * tree_head, 
					   std::string result_dictionary_file_pass, 
					   const std::map<unsigned int, std::string> & the_reverse_phone_alphabet )
{
	List_Node *child_node;
	
	std::vector<std::string> phones;

	std::ofstream result_dictionary_file ( result_dictionary_file_pass.c_str() );

	child_node = as_node(tree_head)->children.first; 
	
	while (child_node)
	{
		add_new_word_in_the_dictionary ( child_node, phones, result_dictionary_file, the_reverse_phone_alphabet );
		child_node = child_node->next;
	}

	result_dictionary_file.close();
	
	return;
}


std::vector<std::string> phone_str_to_vect ( std::string phones_str )
{
	std::vector<std::string> phones;
	std::string phone = "";

	for ( std::size_t phones_str_inx = 0; phones_str_inx <= phones_str.size(); phones_str_inx++ )
	{
		if ( ( phones_str[phones_str_inx] == ' ' ) || ( phones_str_inx == phones_str.size() ) )
		{
			phones.push_back ( phone );
			
			phone = "";					
		} 
		else
		{
			phone += phones_str[phones_str_inx];
		}							
	}

	return phones;
}


int main() {
	
	std::pair < std::map <std::string, unsigned int>, 
				std::map<unsigned int, std::string> > phone_alphabet = form_phone_alphabet ( "phone.txt" );

	std::map<std::string, unsigned int> the_phone_alphabet = phone_alphabet.first;
	std::map<unsigned int, std::string> the_reverse_phone_alphabet = phone_alphabet.second;
	
	//int count = 0;

	//while (count < 10000)
	//{
		Base_Node * tree_head = new Node();	

		tree_head = form_tree (tree_head, "dictionary.txt", the_phone_alphabet );

		std::vector<std::string> vec_phones = phone_str_to_vect("j o0 sh");

		int id = get_id(tree_head, vec_phones, the_phone_alphabet);
		if ( id == 0 )
		{
			std::cout << "There is no sutable word in the tree" << std::endl;		
		}
		else
		{
			std::cout << "The id is " << id << std::endl;
		}

		form_dictionary(tree_head, "result_dictionary_file.txt", the_reverse_phone_alphabet );
  
		//count ++;
		delete tree_head;
	//}
	

	int y;
	std::cin >> y;
	
	return 0;
}
