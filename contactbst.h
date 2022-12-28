#ifndef ContactBST_H
#define ContactBST_H

#include<iostream>
#include "contact.h"
#include "myvector.h"  

using namespace std;

class Node
{
	private:
		string key;
		MyVector<Contact>* contactVector;
		Node* left;
		Node* right;
	public:
		Node();                                               //default constructor
		Node(string key, MyVector<Contact>* contactVector);   //constructor with arguments
		~Node();                                              //destructor
		string getKey();                                      //returns the key of the node
		MyVector<Contact>* getData();                         //returns the vector of contacts
		void addToVect(Contact cont);                         //adds a contact to the end of the vector
		Contact removeFromVect(int index);                    //removes the contact from the vector
		void contactDisplay();                                //displays the contacts saved in the vector
		int vectSize();                                       //returns the vector size
		friend class ContactBST;
};

//=============================================================================
class ContactBST
{
	private:
		Node* root;
	public:
		ContactBST();									  //constructor
		~ContactBST();									  //destructor
		Node* getRoot();						          //returns the root of the Tree
		Node* add(Node* ptr,string key, Contact* data);	  //add key into tree/subtree with root ptr
		Node* update(Node* ptr, string key);              //Edit the node with key
		Node* findMin(Node *ptr);				          //return the Node with minimum key value from a tree with root ptr
		Node* del(Node* ptr,string key);		          //Delete a node with key from the tree/subtree with root
		Node* search(Node* ptr,string key);	              //Find and returns the node with key
		bool markFav(Node* ptr, string key);              //Mark a contact as favorite 
		bool unmarkFav(Node* ptr, string key);            //Unmark a contact as favorite 
		void printASC(Node* ptr);			              //Print the data at nodes in an ascending order
		void printDES(Node* ptr);					      //Print the data at nodes in a descending order
		void printFav(Node* ptr);                         //Print the favorite data at nodes in an ascending order
		int importCSV(Node* ptr, string path);            //Load all the contacts from the CSV file to the BST
		int exportCSV(Node* ptr, string path);            //Export all the contacts from the BST to a CSV file in an ascending order

	public:	//helper methods
		void insert_helper(string key, Contact* data);	  //Helper method for insert method
		void remove_helper(string key);					  //Helper method for remove method
};

#endif