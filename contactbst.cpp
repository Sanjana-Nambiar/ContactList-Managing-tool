#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "contactbst.h"
#include "myvector.h"  
#include "contact.h"

using namespace std;

	Node::Node()//default constructor
	{
		this->key = " ";
		this->contactVector = new MyVector<Contact>();
		this->left = nullptr;
		this->right = nullptr;
	}
	Node::Node(string key, MyVector<Contact>* contactVector) //constructor with arguments
	{
		this->key = key;
		this->contactVector = contactVector;
		this->left = nullptr;
		this->right = nullptr;
	}
	Node::~Node() //destructor
	{
		delete contactVector;
	}
	string Node::getKey() //returns the key of the node
	{ 
		return this->key;
	}
	MyVector<Contact>* Node::getData() //returns the vector of contacts
	{ 
		return this->contactVector;
	}
	void Node::addToVect(Contact cont) //adds a contact to the end of the vector
	{ 
		contactVector->push_back(cont); 
	}
	Contact Node::removeFromVect(int index) //removes the contact from the vector
	{ 
		return(contactVector->erase(index)); 
	}
	void Node::contactDisplay()  //displays the contacts saved in the vector
	{ 
		contactVector->display(); 
	}
	int Node::vectSize() //returns the vector size
	{ 
		return(contactVector->size()); 
	}

	ContactBST::ContactBST() //constructor
	{
		root = nullptr;
	}									
	ContactBST::~ContactBST() //destructor
	{
		while(root)
			root = del(root,root->key);	
	}
	Node* ContactBST::getRoot() //returns the root of the Tree
	{
		return(root);
	}
	Node* ContactBST::add(Node* ptr,string key, Contact* data) //add key into tree/subtree with root ptr
	{
		if (ptr == nullptr) // if reach the end then add the new node
		{
			MyVector<Contact>* contactVector = new MyVector<Contact>();
			contactVector->push_back(*data);
			ptr = new Node(key, contactVector);
			return ptr;
		}

		if (ptr->key == key)//for checking whether the key already exists or not  
		{
			ptr->addToVect(*data);
			return ptr;
		}

	  //traversing through recursion
		if   (ptr->key < key)
	        ptr->right = add(ptr->right, key, data);
	    else 
	        ptr->left = add(ptr->left, key, data);
	    return ptr;
	}

	Node* ContactBST::findMin(Node *ptr) //return the Node with minimum key value from a tree with root ptr
	{
		if(ptr == nullptr)//if there is no nodes
			return nullptr;

		if(ptr->left == nullptr)
			return ptr;
		    
			return (findMin(ptr->left));
	}

Node* ContactBST::update(Node* ptr, string key) //Edit the node with key
{
	string first, last, email, phone, city, country, newKey;
	MyVector<Contact>* newVect = new MyVector<Contact>();
	Contact newCont;

	Node* updatePtr = search(getRoot(), key);//for checking whether the node with the key is ther or not 
	if (updatePtr == nullptr)
	{
		cout << "The key is not there\n";
		return updatePtr;
	}
	updatePtr->contactDisplay();//displays the contact
	newVect = updatePtr->getData(); 

	cout << endl;
	
	int field, num;
	cout <<"Please select the record you want to edit : "; cin >> num;
	newCont = updatePtr->getData()->at(num-1);

	string ans;
	bool edit = true;
	while(edit)
	{
		cout << "Which field do you want to edit? 1) First Name, 2) Last Name, 3) Email, 4) Phone#, 5) City, or 6) Country: "; cin >> field;
		switch(field)
		{
		case 1:	{
			cout << "Please enter the new First Name: "; cin >> first;
			int size = updatePtr->vectSize();
			if(size == 1) //if there is only one element then delete the node 
				{ root = del(root, key);}
			else//else just remove the contact from the vector
				{ newCont = updatePtr->removeFromVect(num-1); }

			last = newCont.getLname();
			newCont.setFname(first);
			newKey = first + " " + last;
			
			insert_helper(newKey, &newCont);//insert new contact as the first name changes key changes
			updatePtr = search(getRoot(), newKey);
			break;
		}
		case 2:	{
			cout << "Please enter the new Last Name: "; cin >> last;
			int size = updatePtr->vectSize();
			if(size == 1) 
				{ root = del(root, key);}
			else
				{ newCont = updatePtr->removeFromVect(num-1); }

			first = newCont.getFname();
			newCont.setLname(last);
			newKey = first + " " + last;
			
			insert_helper(newKey, &newCont);//insert new contact as the last name changes key changes
			updatePtr = search(getRoot(), newKey);
			break;
		}
		case 3:{
			cout << "Please the new Email: "; cin >> email;
			updatePtr->getData()->at(num-1).setEmail(email);//updating the email
			break;
		}
		case 4:{
			cout << "Please the new Phone#: "; cin >> phone;
			updatePtr->getData()->at(num-1).setPhone(phone);//updating the phone number
			break;
		}
		case 5:{
			cout << "Please the new City: "; cin >> city;
			updatePtr->getData()->at(num-1).setCity(city);//updating the city
			break;
		}
		case 6:{
			cout << "Please the new Country: "; cin >> country;
			updatePtr->getData()->at(num-1).setCountry(country);//updating the country
			break;
		}
		default:{
			cout << "Wrong Option\n";
			break;
		}
		}
		cout << "Do you want to edit another field (y/n)? "; cin >> ans;
		if(ans == "y" || ans == "Y"){edit = true;}
		else if(ans == "n" || ans == "N"){edit = false;}
		else{cout << "Wrong Option"; edit = true;}
		cout << endl;
	}
	updatePtr->contactDisplay();
	cout << updatePtr->getData()->at(num-1).getFname()<<" "<<updatePtr->getData()->at(num-1).getLname()<<" ("<<updatePtr->getData()->at(num-1).getEmail()
			<<") has been successfully updated" << endl;	
	return(root);
}

Node* ContactBST::del(Node* ptr,string key) //Delete a node with key from the tree/subtree with root
{
	Node* check = search(root, key);
	if (check == nullptr)
	{
		cout << "The key is not there\n";
		return ptr;
	}	
	if(ptr == nullptr)//returns null if we reach the end of the tree 
		return nullptr;

	// case 1: if the left and the right is null that the node to be removed is a leaf
	if(ptr->key == key && ptr->left == nullptr && ptr->right == nullptr)
	{
		delete ptr;
		return nullptr;
	}
	//case 2: if the node to be removed just has a right side child
	else if(ptr->key == key && ptr->left == nullptr)
	{
		Node* temp = ptr->right; 
		delete ptr; 
		ptr = temp; 
		return ptr; 
	}
	//case 3: if the node to be removed just has a left side child
	else if(ptr->key == key && ptr->right == nullptr)
	{		
		Node* temp = ptr->left; 
		delete ptr; 
		ptr = temp; 
		return ptr; 
	}
	//case 4: if the node has both right and left children
	else if(ptr->key == key && ptr->left && ptr->right)
	{
		Node* temp = findMin(ptr->right); 
		ptr->key = temp->key;
		ptr->contactVector = temp->contactVector;
		ptr->right = del(ptr->right,ptr->key);
	}
	//traversing through recursion
	else if(ptr->key < key) 
		ptr->right = del(ptr->right,key);
	else
		ptr->left = del(ptr->left, key);
	return ptr;
} 

Node* ContactBST::search(Node* ptr,string key) //Find and returns the node with key
{
	if (ptr == nullptr)//if there is no nodes
	{
		return nullptr;
	}	
	//case 1: if we find the node with the same key then return the node
    else if (ptr->key == key)
    {
       	return ptr;
    }    
    //case 2: if we reach the last node and still we didnt get the node then we return null
    else if (ptr->left == nullptr && ptr->right == nullptr)
    {
    	return nullptr;
    }
    //traversing through recursion
    else if (ptr->key < key)
    	return search(ptr->right, key);
 	else
    	return search(ptr->left, key);
}
bool ContactBST::markFav(Node* ptr, string key) //Mark a contact as favorite 
{
	Node* fav;
	fav = search(getRoot(),key);
	if (fav ==  nullptr) 
	{
		return false;
	}

	fav->contactDisplay();
	cout << endl;
	
	int num;
	cout <<"Please select the record you want to mark as favorite : ";cin >> num;
	fav->getData()->at(num-1).setIsFav(1);

	cout << fav->getData()->at(num-1).getFname()<<" "<<fav->getData()->at(num-1).getLname()<<" ("<<fav->getData()->at(num-1).getEmail()
		<<") has been successfully marked as favorite" << endl;

	return true; 
}

bool ContactBST::unmarkFav(Node* ptr, string key) //Unmark a contact as favorite 
{
	Node* fav;
	fav = search(getRoot(),key);
	if (fav ==  nullptr) 
	{
		return false;
	}

	fav->contactDisplay();
	cout << endl;

	int num;
	cout <<"Please select the record you want to mark as unfavorite : ";cin >> num;
	fav->getData()->at(num-1).setIsFav(0);

	cout << fav->getData()->at(num-1).getFname()<<" "<<fav->getData()->at(num-1).getLname()<<" ("<<fav->getData()->at(num-1).getEmail()
		<<") has been successfully marked as unfavorite" << endl;

	return true;
}
void ContactBST::printASC(Node* ptr) //Print the data at nodes in an ascending order
{
	if (ptr != nullptr)// till it reaches the end
	{
        printASC(ptr->left);
        int size = ptr->vectSize();
	    for(int i = 0; i<size; i++)
	    {
	    	ptr->getData()->at(i).print();	
	    }
        printASC(ptr->right);
    }
}
void ContactBST::printDES(Node* ptr) //Print the data at nodes in a descending order
{
	if (ptr != nullptr)// till it reaches the end
	{
        printDES(ptr->right);
        int size = ptr->vectSize();
	    for(int i = 0; i<size; i++)
	    {
	    	ptr->getData()->at(i).print();	
	    }
        printDES(ptr->left);
    }
}
void ContactBST::printFav(Node* ptr) //Print the favorite data at nodes in an ascending order
{
	if (ptr == nullptr)	{ return; }

    printFav(ptr->left);
    int size = ptr->vectSize();
    for(int i = 0; i<size; i++)
    {
    	if(ptr->getData()->at(i).getIsFav() == 1)
    	{
    		ptr->getData()->at(i).print();	
    	}
    }
    printFav(ptr->right);
}
int ContactBST::importCSV(Node* ptr, string path) //Load all the contacts from the CSV file to the BST
{
	int check = 0;
	string delim;
	string fname, lname, email, phone, city, country, fav;

	ifstream contact (path, ios::in);//declares an ifstream object
	int isfav;
    
    if (contact.is_open())//opens the file
    {
        string line;
        while( getline(contact,line) )//till last line
        {
            stringstream s(line);

            //gets the word till ',' here comma is taken as the delimiter
            getline(s,fname,','), getline(s,delim,' '); getline(s,lname,','), getline(s,delim,' '); 
            getline(s,email,','), getline(s,delim,' '); getline(s,phone,','), getline(s,delim,' '); 
            getline(s,city,','), getline(s,delim,' '); getline(s,country,','), getline(s,delim,' '); getline(s,fav,' '); 
            isfav = stoi(fav);//converts string to integer
            Contact* C = new Contact(fname, lname, email, phone, city, country, isfav);

            string key = fname + " " + lname;
            insert_helper(key, C);
            check++;
        }
	}
	if(check == 0) return -1; 

	return (check);
}
int ContactBST::exportCSV(Node* ptr, string path) //Export all the contacts from the BST to a CSV file in an ascending order
{
	int check = 0;
	
	ofstream foutAd(path, ios::app);//declaring a ofstream file fout
	if(foutAd)
	{
		if (ptr != nullptr)// till it reaches the end
		{
	        exportCSV(ptr->left,path);
	        MyVector<Contact>* Toprint = new MyVector<Contact>();
	        Toprint = ptr->getData();
	        for (int i = 0; i < Toprint->size(); i++)
	        {
				Contact C = Toprint->at(i);
				foutAd << C.getFname() <<", "<< C.getLname() <<", "<< C.getEmail() <<", " 
				<< C.getPhone() <<", "<< C.getCity() <<", " << C.getCountry() <<", " << C.getIsFav() <<endl;
			}
			check++;
	       exportCSV(ptr->right,path);
	    }
	  foutAd.close();
	}
	else
	{
		perror("Error::");//for printing error
		return -1;
	}
	return (check);
}

void ContactBST::insert_helper(string key, Contact* data) //Helper method for insert method
{
	root = add(root, key, data);
}
void ContactBST::remove_helper(string key) //Helper method for remove method
{
	Node* check = search(root, key);
	if (check == nullptr)
	{
		cout << "The key is not there\n";
		return;
	}
	check->contactDisplay();
	cout << endl;
	
	int field, num;
	cout <<"Please select the record do you want to delete : "; cin >> num;
   	
 	int size = check->vectSize();
	if(size > 1)//check the size of the vector and then delete
	{
		check->removeFromVect(num-1);
	}
	else
	{
		del(root, key);
	}
	cout << "The contact record has been successfully deleted!\n";
}
