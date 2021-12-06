//*****************************************************************************************
//Program by: Adam LaFleur
//Date: March 8, 2019
//Class: CS163 - Data Structures
//Program: #4
//File: assignment04.cpp
//Purpose: The purpose of this program is to keep track of information pertaining to CS concepts
//or topics; and to be able to retrieve the topics and print them out, also have the option to perform
//various chainges to the data set.
//main.cpp has the purpose of controlling the program and inputting data to be sent to the ADT. 
//*****************************************************************************************
#include <iostream>
#include <iomanip>
#include <cstring>
#include "bst.h"

using namespace std;



void add(entry &insert);
void print(const entry pentry);
void status(int num);
void remove(entry &remove);



// The purpose of main is the initialize and run the program, main has a menu that gives the user an
// option of what they want to do, the menu repeats until the user specifices when to stop. The
// main program also creates a struct entry, fills it, and then sends it to the adt to be added or sends an array
// of entries to the ADT and receives matching entries back. The user is given the options of adding a entry, 
// removing an entry, retrieve the definition for an entry. retrieving the height of the tree, determining if the
// tree is efficient, displaying all, displaying all entries that fit insite a range, and finally quitting the 
// program.
int main()
{
	entry insert; //entry objects used to grab data from ADT
	bst tree;
	char input[64], first[6], last[6];
	char * retrieve = nullptr;
	int choice = 0, num = 0; //choice used to control which menu option selected, num is used to record ADT return values
	bool control = true; //Controls whether the program loops or not

	cout << "----------------------------------------------" << endl;
        cout << "*************** Program #3: BST **************" << endl;
        cout << "----------------------------------------------" << endl;
	while(control)
	{
		num = 0;
		cout << "Please choose an option: " << endl;
		cout << "01. Add a new CS concept or term." << endl;
		cout << "02. Remove a CS concept or term." << endl;
		cout << "03. Retrieve definition of a CS concept or term." << endl;
		cout << "04. Retrieve the height of the tree." << endl;
		cout << "05. Is the BST efficient?" << endl;
		cout << "06. Display all the CS concepts or terms." << endl;
		cout << "07. Display all CS concents or terms within a Range." << endl;
		cout << "08. Quit client program." << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Please enter a choice: ";
		cin >> choice;
		cin.ignore();
		cout << endl;
		switch(choice)
		{
			case 1:
				add(insert);
				num = tree.add_entry(insert);
				remove(insert);
				status(num);
				break;
			case 2:
				cout << "Please entet the name of the CS Concept or Term you want to remove: ";
				cin.getline(input, sizeof(input));
				num = tree.remove_entry(input);
				status(num);
				break;
			case 3:
				cout << "Please enter the name of the CS Concept or Term you want to retrieve: ";
				cin.getline(input, sizeof(input));
				num = tree.retrieve_entry(input, retrieve);
				if(retrieve)
				{
					cout << endl << "Description: " << retrieve << endl;
					delete [] retrieve;
				}
				status(num);	
				break;
			case 4:
				num = tree.get_height();
				cout << "The height of the tree is: " << num << endl;
				status(num);
				break;
			case 5:
				num = tree.is_efficient();
				cout << "Is the BST efficient?: ";
				if(num == 1)
				{
					cout << "Yes" << endl;
				}
				else
				{
					cout << "No" << endl;
				}
				status(1);
				break;
			case 6:
				cout << "The list of all CS Concepts and Terms: " << endl;
				cout << "--------------------------------------------------------" << endl << endl;
				num = tree.display_all();
				cout << "--------------------------------------------------------" << endl;
				status(num);
				break;
			case 7:
				cout << "Please enter the range. " << endl;
				cout << "--------------------------------------------------------" << endl;
				cout << "First: ";
				cin.getline(first, sizeof(first));
				cout << "Last: ";
				cin.getline(last, sizeof(last));
				cout << endl;
				if(first && last)
				{
					cout << "The list of all CS Concepts and Terms within the Range of " << first << " and " << last << ": " << endl;
					cout << "--------------------------------------------------------" << endl << endl;
					num = tree.display_range(first, last);
					cout << "--------------------------------------------------------" << endl;
				}
				status(num);
				break;
			case 8:
				control = false;
				status(1);
				break;
			default:
				break;
		}
	}
	return 0;
}



//Function used to fill a struct to be sent into the ADT or anywhere else in the program, 
//takes in an etry type using pass by reference
void add(entry &insert)
{
	char input[1000];
	cout << "Please enter the name of the CS Concept or Term: ";
	cin.getline(input, sizeof(input));
	insert.name = new char[strlen(input) + 1];
	strcpy(insert.name, input);

	cout << "Please enter the desciption of the concept: ";
	cin.getline(input, sizeof(input));
	insert.description = new char[strlen(input) + 1];
	strcpy(insert.description, input);

	cout << "Please enter the data structure this relates to: ";
	cin.getline(input, sizeof(input));
	insert.structure = new char[strlen(input) + 1];
	strcpy(insert.structure, input);
}



// The purpose of print is to print off the entry data that is returned back from the
// ADT, takes a entry data type
void print(const entry to_print)
{
	cout << endl;
	cout << "Name: " << to_print.name << endl;
	cout << "Description: " << to_print.description << endl;
	cout << "Data Structure: " << to_print.structure << endl;
	cout << endl;
}



//The purpose of remove is to delete a data entry after it is sent in or returned back,
//it takes a pass by reference entry argument
void remove(entry &to_delete)
{
	if(to_delete.name)
	{
		delete [] to_delete.name;
		to_delete.name = nullptr;
	}
	if(to_delete.description)
	{
		delete [] to_delete.description;
		to_delete.description = nullptr;
	}
	if(to_delete.structure)
	{
		delete [] to_delete.structure;
		to_delete.structure = nullptr;
	}
}



// Failure will be printed out, if 1 or greater is supplied then Success will be printed out.
void status(int num)
{
	cout << endl;
	cout << "Status: ";
	if(num == 0)
	{
		cout << "Failure! / Empty List!" << endl;
	}
	if(num > 0)
	{
		cout << "Success!" << endl;
	}
	cout << endl;
}
