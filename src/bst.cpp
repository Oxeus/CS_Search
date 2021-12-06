//*****************************************************************************************
//Program by: Adam LaFleur
//Date: March 8, 2019
//Class: CS163 - Data Structures
//Program: #4
//File: bst.cpp
//Purpose: The purpose of this program is to keep track of information pertaining to CS concepts
//or topics; and to be able to retrieve the topics and print them out, also have the option to perform
//various chainges to the data set.
//table.h has the purpose of containing the algorithms to add to the bst, remove from the bst,
//retrieve a definition from the bst, retrive the height of the bst, determine if the bst is effificient,
//printing the whole bst, and printing the bst nodes that match the range given.Also the ADT reads in 
//data from a file in its constructor.
//*****************************************************************************************
#include "bst.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <math.h>

using namespace std;



//Has the purpose of reading in a data file and creating an entry object to be sent to the add function
//Inputs a data file outputs an entry
int bst::read()
{
	entry insert;
        ifstream inFile;
        char name[64], description[1000], structure[64];

        inFile.open("data.txt");
        while(!inFile.eof() && inFile.getline(name, 64, '|'))
        {
                //name
                insert.name = new char[strlen(name) + 1];
                strcpy(insert.name, name);

                //Description
		inFile.getline(description, 1000, '|');
               	insert.description  = new char[strlen(description) + 1];
		strcpy(insert.description, description);

		//Structure
		inFile.getline(structure, 64);
		insert.structure = new char[strlen(structure) + 1];
		strcpy(insert.structure, structure);

		//Add to BST
                add_bst(root, insert);
                delete_entry(insert);
        }
        inFile.close();
	return 1;
}



//Constructor used to initialize root to null and calls to read to readin data
bst::bst()
{
	root = nullptr;
	read();
}



//This function recursively deletes the whole bst. Takes in a pass by reference root
//as an argument
int bst::remove_all(node *& root)
{
	int count = 0;
	if(!root) return count;
	count = 1 + remove_all(root->left) + remove_all(root->right);
	if(root)
	{
		delete_entry(root->data);
		delete root;
		root = nullptr;
	}
	return count;
}



//Deconstructor used to deallocate memory in the table, calls to remove_all to
//recursively delete bst
bst::~bst()
{
	remove_all(root);
	root = nullptr;
}



//Function used to copy data from one entry to another, the first input is a const entry
//thats is the entry to copy from and the second input is a pass by reference copy that
//can be accessed and changed. The output is a pass by reference entry type.
int bst::copy_entry(const entry to_copy, entry &copy)
{
	if(!to_copy.name) return 0;

	if(to_copy.name)
	{
		copy.name = new char[strlen(to_copy.name) + 1];
		strcpy(copy.name, to_copy.name);
	}
	if(to_copy.description)
	{
		copy.description = new char[strlen(to_copy.description) + 1];
		strcpy(copy.description, to_copy.description);
	}
	if(to_copy.structure)
	{
		copy.structure = new char[strlen(to_copy.structure) + 1];
		strcpy(copy.structure, to_copy.structure);
	}
	return 1;
}



//Print_entry has the purpose of printing off an entry.  Takes in an imput of type struct
//entry and outputs/prints the data listed in the struct.
int bst::print_entry(const entry to_print)
{
	if(!to_print.name && !to_print.description && !to_print.structure) return 0;

	if(to_print.name)
	{
		cout << "Name: " << to_print.name << endl;
	}
	if(to_print.description)
	{
		cout << "Description: " << to_print.description << endl;
	}
	if(to_print.structure)
	{
		cout << "Structure: " << to_print.structure << endl;
	}
	return 1;
}



////Used to delete an entry, this function was written so that there wouldn't be additional delete
//functions everywhere. Takes in a pass by reference struct entry that can be edited and deleted.
int bst::delete_entry(entry &to_del)
{	
	if(!to_del.name && !to_del.description && !to_del.structure) return 0;
	
	if(to_del.name)
	{
		delete [] to_del.name;
	}
	if(to_del.description)
	{
		delete [] to_del.description;
	}
	if(to_del.structure)
	{
		delete [] to_del.structure;
	}
	return 1;
}



//Add
//Recursive Function to add a concept to the bst. Takes is pass by
//reference node pointer root and a const entry insert.
int bst::add_bst(node *& root, const entry insert)
{
	int num = 0;
	if(!root)
	{
		root = new node;
		copy_entry(insert, root->data);
		root->left = root->right = nullptr;
		return 1;
	}
	if(strcmp(root->data.name, insert.name) > 0)
	{
		num = add_bst(root->left, insert);
	}
	else
	{
		num = add_bst(root->right, insert);
	}
	return num;
}



//Wrapper for recursive add_bst. Takes in a const entry insert
//as a argument.
int bst::add_entry(const entry insert)
{
	return add_bst(root, insert);
}



//Remove
//Recursive delete function that removes user specified name from
//the list. Takes in a pass by reference node pointer root and a const char name
int bst::remove_bst(node *& root, const char * name)
{
	int remove = 0;
	if(!root) return remove;
	if(strcmp(root->data.name, name) == 0)
	{
		node * curr = nullptr;
		node * prev = nullptr;
		if(!root->left && !root->right)
		{
			delete_entry(root->data);
			delete root;
			root = nullptr;
		}
		else if((root->left && !root->right) || (!root->left && root->right))
		{
			if(root->left)
			{
				curr = root;
				root = root->left;
				delete_entry(curr->data);
				delete curr;
			}
			else
			{
				curr = root;
				root = root->right;
				delete_entry(curr->data);
				delete curr;
			}
		}
		else if(root->left && root->right)
		{
			if(!root->right->left)
			{ 
				delete_entry(root->data);
				copy_entry(root->right->data, root->data);
				curr = root->right;
				root->right = curr->right;
				delete curr;
			}
			else if(root->right->left)
			{
				prev = root->right;
				curr = root->right;
				while(curr->left != NULL)
				{
					prev = curr;
					curr = curr->left;
				}
				delete_entry(root->data);
				copy_entry(curr->data, root->data);
				prev->left = curr->right;
				delete curr;
			}
		}
		return 1;
	}
	if(strcmp(root->data.name, name) > 0)
	{
		remove = remove_bst(root->left, name);
	}
	else if(strcmp(root->data.name, name) < 0)
	{
		remove = remove_bst(root->right, name);
	}
	return remove;
	
}



//Wrapper Function for remove_bst. Takes in a const char name as an
//argument
int bst::remove_entry(const char * name)
{
	if(!root) return 0;
	return remove_bst(root, name);
}



//Retrieve
//Function used to recursively find and send back the description for 
//a CS concept or topic. Takes in a node pointer root, const char name,
//and a pass by reference char retrieve thats used to send back retrieved description.
int bst::retrieve_bst(node * root, const char * name, char *& retrieve)
{
	int found = 0;
	if(!root) return found;
	if(strcmp(root->data.name, name) == 0)
	{
		retrieve = new char[strlen(root->data.description) + 1];
		strcpy(retrieve, root->data.description);
		return 1;
	}
	if(strcmp(root->data.name, name) > 0)
	{
		found = retrieve_bst(root->left, name, retrieve);
	}
	else if(strcmp(root->data.name, name) < 0)
	{
		found = retrieve_bst(root->right, name, retrieve);
	}
	return found;
}



//Wrapper Function for retrieve_bst. Takes in a const char name and a pass
//by reference char retrieve
int bst::retrieve_entry(const char * name, char *& retrieve)
{
	if(!root) return 0;
	return retrieve_bst(root, name, retrieve);
}



//Get_height
//Recursive function used to find the general height of the tree. Takes in a 
//node pointer root as an argument. Returns the height of the tree in return
//statement.
int bst::get_height_bst(node * root)
{
	if(!root) return 0;
	return max(get_height_bst(root->left) + 1, get_height_bst(root->right) + 1);
}



//Wrapper function for get_height_bst.
int bst::get_height()
{
	if(!root) return 0;
	return get_height_bst(root);
}



//Is Efficient
//Recursive function to grab the total number of nodes in the bst. Takes in 
//node pointer root as an argument.
int bst::is_efficient_bst(node * root)
{
	if(!root) return 0;
	return 1 + is_efficient_bst(root->left) + is_efficient_bst(root->right);
}



//Wrapper function for is_efficient bst. Also accesses height function to find the number
//of nodes to make the tree complete for that height. The function compares the current
//number of nodes and the needed number of nodes to make it complete and returns 0 if
//they are not equal and 1 if they are.
int bst::is_efficient()
{
	if(!root) return 1;
	if(is_efficient_bst(root) == (pow(2, get_height()) - 1))
	{
		return 1;	
	}
	return 0;
}



//DisplayAll
//Function used to recursively display all nodes in the bst in order. Takes in a node 
//pointer root as an argument and calls to print_entry function to output data.
int bst::display_all_bst(node * root)
{
	if(!root) return 0;
	display_all_bst(root->left);
	print_entry(root->data);
	cout << endl;
	display_all_bst(root->right);
	return 1;
}



//Wrapper function for display_all.
int bst::display_all()
{
	if(!root) return 0;
	return display_all_bst(root);
}



//Display Range
//Recursively prints out the data in the range of the char arrays entered by the user.
//Takes in a node pointer root, and two char arrays first and last as arguments. Outputs
//the nodes that exist in range of the two char arrays.
int bst::display_range_bst(node * root, char * first, char * last)
{
	if(!root) return 0;
	display_range_bst(root->left, first, last);
	if((strcmp(root->data.name, first) >= 0) && (strcmp(root->data.name, last) <= 0))
	{
		print_entry(root->data);
		cout << endl;
	}
	display_range_bst(root->right, first, last);
	return 1;
}


//Wrapper function for display_all_bst. Takes in a char array argument first and last.
int bst::display_range(char * first, char * last)
{
	if(!root) return 0;
	return display_range_bst(root, first, last);
}
