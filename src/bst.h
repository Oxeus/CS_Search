//*****************************************************************************************
//Program by: Adam LaFleur
//Date: March 8, 2019
//Class: CS163 - Data Structures
//Program: #4
//File: bst.h
//Purpose: The purpose of this program is to keep track of information pertaining to CS concepts
//or topics; and to be able to retrieve the topics and print them out, also have the option to perform
//various chainges to the data set.
//table.h has the purpose of defining the ADT structure and defining the entry structure
//*****************************************************************************************

struct entry {
	char * name;
	char * description;
	char * structure;
};



class bst
{
	public:
		bst();
		~bst();
		int add_entry(const entry insert);
		int remove_entry(const char * name);
		int retrieve_entry(const char * name, char *& retrieve);
		int get_height();
		int is_efficient();
		int display_all();
		int display_range(char * first, char * last);

	private:
		struct node {
			entry data;
			node * left;
			node * right;
		};
		node * root;

		int read();
		int remove_all(node *& root);
		int add_bst(node *& root, const entry insert);
		int remove_bst(node *& root, const char * name);
		int retrieve_bst(node * root, const char * name, char *& retrieve);
		int get_height_bst(node * root);
		int is_efficient_bst(node * root);
		int display_all_bst(node * root);
		int display_range_bst(node * root, char * first, char * last);

		int copy_entry(const entry to_copy, entry &copy);
		int print_entry(const entry to_print);
		int delete_entry(entry &to_del);
};
