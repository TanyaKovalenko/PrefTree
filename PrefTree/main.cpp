#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <map> 
#include "Node.h"
#include "Phone.h"

// Variable PHONE_ALPHABET_SIZE contains 
// the number of the different phones in the phones' alphabets 
const short int PHONE_ALPHABET_SIZE = 59;

// This function from the file of the phones 
// creates and returns a forward and reverse alphabets phonemes, 
// which are essentially maps.
std::pair < std::map < std::string, unsigned int >, 
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

// Helper to change type
inline Node * as_node(Base_Node * node)
{
	return dynamic_cast<Node *>(node);
}

// This function find and returns the ID of the word 
// eccording to it's ronunciation ( recruitment of phonemes ),
// if it exists in the dictionary

std::pair<int, bool> get_id( Base_Node * tree_head, 
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
					return std::make_pair(child_node->node->get(), true);
				} 
				if (child_node->next)
				{
					child_node = child_node->next;
				} 
				else
				{
					return std::make_pair(0, false);
				}
			}
		} 
		else 
		{
			if (child_node->node->is_id() && (phones_inx == phones.size()))
			{
				return std::make_pair(child_node->node->get(), true);
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
							return std::make_pair(0, false);
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

	return std::make_pair(0, false);
}


void add_word_in_the_tree ( Base_Node * tree_head, 
						    const std::vector < unsigned int > & phones, 
							int & node_count, 
							const unsigned int & word_id )
{
	Base_Node * node = tree_head;
	List_Node *node_to_compare;
	List_Node *child_node;
	bool need_add = false;

	for ( std::size_t phones_inx = 0; phones_inx < phones.size(); phones_inx++ )
	{
	// add new phone in the tree
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

		Base_Node *new_id_node = new Base_Node();
		new_id_node->set(word_id, true, false);
		as_node(node)->children.push(new_id_node);
		node_count++;

		return;
}


// This function (in accordance with the file that contains the dictionary)
// forms a network (tree) of the phonemes 
// and returns a pointer to the head of the tree
Base_Node * form_tree ( Base_Node * tree_head, 
					    const std::string & dictionary_file_pass, 
						const std::map < std::string, unsigned int > & the_phone_alphabet )
{
	int node_count = 0;
	std::string line;  
	std::ifstream dictionary_file ( dictionary_file_pass.c_str() );

	if ( dictionary_file.is_open() )
	{			
		unsigned int word_id;
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
			
			// add new word in the tree

			add_word_in_the_tree(tree_head, phones, node_count, word_id);

			phones.clear();
		}	
	}

	dictionary_file.close();

	std::cout << "Count of the nodes in the net are " << node_count << std::endl;

	return tree_head;
}


// This function add next word ( string "phonemes#ID_of_the_phonemes") 
// from the network (tree) to dictionary file.
void add_new_word_in_the_dictionary ( List_Node * child_node, 
									  std::vector < std::string > & phones, 
									  std::ofstream & result_dictionary_file,
									  const std::map < unsigned int, std::string > & the_reverse_phone_alphabet ) 
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


// This function restores from the network a dictionary file.
// Every dictionary's string looks like: "phonemes#ID_of_the_phonemes".
void form_dictionary ( Base_Node * tree_head, 
					   std::string result_dictionary_file_pass, 
					   const std::map < unsigned int, std::string > & the_reverse_phone_alphabet )
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

// This function reterns vector of the phones, that it forms from the phones_string
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
		
	std::pair < std::map < std::string, unsigned int >, 
				std::map < unsigned int, std::string > > phone_alphabet = form_phone_alphabet ( "phone.txt" );

	std::map<std::string, unsigned int> the_phone_alphabet = phone_alphabet.first;
	std::map<unsigned int, std::string> the_reverse_phone_alphabet = phone_alphabet.second;
	
	Base_Node * tree_head = new Node();	

	// Form phones tree (network)

	tree_head = form_tree (tree_head, "dictionary.txt", the_phone_alphabet );

	// Find the id of the word
		
	std::vector<std::string> vec_phones = phone_str_to_vect ( "a0 t" );

	std::pair<int, bool> id = get_id(tree_head, vec_phones, the_phone_alphabet);

	if ( !id.second )
	{
		std::cout << "There is no sutable word in the tree" << std::endl;		
	}
	else
	{
		std::cout << "The id is " << id.first << std::endl;
	}

	// Form dictionary file from the tree ( network)
	form_dictionary(tree_head, "result_dictionary_file.txt", the_reverse_phone_alphabet );
  
	// Delete tree
	delete tree_head; 

	return 0;
}
