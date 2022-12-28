//=================================================================================
// Name         : DS Assignment#3 
// Author       : Sanjana Nambiar
// Version      : 2.0
// Date Created : 03-20-2022
// Date Modified: 04-10-2022
// Description  : Starter Code for Contact Management System using BST Tree in C++
// Copyright © 2022 Khalid Mengal and Mai Oudah. All rights reserved.
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include "contact.h"
#include "contactbst.h"

//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"import <path>      :Import contacts from a CSV file"<<endl
		<<"export <path>      :Export contacts to a CSV file"<<endl
		<<"add                :Add a new contact"<<endl
		<<"edit <key>         :Update a contact's details"<<endl
		<<"del <key>          :Delete a contact"<<endl
		<<"searchFor <key>    :Search for a contact"<<endl
		<<"markfv <key>       :Mark as favourite"<<endl
		<<"unmarkfv <key>     :Unmark as favourite"<<endl
		<<"printASC           :Print contacts in ascending order"<<endl
		<<"printDES           :Print contacts in descending order"<<endl
		<<"printfv            :Print all favourite contacts"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================
int main(void)
{

	ContactBST myContactBST;
	listCommands();
	cout << endl;
	string user_input;
	string command;
	string key;

	cout<<">";

	while(true)
	{
		getline(cin,user_input,'\n');

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,key);

		if( command =="import")	
		{ 
			int count = myContactBST.importCSV(myContactBST.getRoot(), key); 
			cout <<"Total "<<count<<" number of contacts has been imported\n";
			cout << endl;
		}
		else if( command =="export") 
		{ 
			int count = myContactBST.exportCSV(myContactBST.getRoot(), key); 
			cout <<"All the contacts has been exported\n";
			cout << endl;
		}
		else if( command == "add") 
		{
			string first, last, email, phone, city, country, fav;
			bool isfav = false;
			cout << "Please enter the details of the contact:\n";
			cout << "First Name: "; cin >> first;
			cout << "Last Name: "; cin >> last;
			cout << "Email: "; cin >> email;
			cout << "Phone#: "; cin >> phone;
			cout << "City: "; cin >> city;
			cout << "Country: "; cin >> country;
			cout << "Do you want to add the contact in your favourites (y/n): "; cin >> fav;
			if(fav == "Y" || fav == "y") {isfav = true;}
			else if(fav == "N" || fav == "n") {isfav = false;}
			else {cout << "Wrong input for making the contact favourite or not\n";}

			string contKey = first + " " + last;
			Contact* cont = new Contact (first, last, email, phone, city, country, isfav);
			myContactBST.insert_helper(contKey, cont);
			cout << "Contact " << contKey << " has been successfully added!\n";
			cout << endl;
		}
		else if( command == "del") { myContactBST.remove_helper(key); cout << endl; }
		else if( command == "edit") { myContactBST.update(myContactBST.getRoot(), key); cout << endl; }
		else if( command =="searchFor")
		{
			Node* ptr = myContactBST.search(myContactBST.getRoot(), key);
			if (ptr == nullptr) { cout << "The key is not there\n"; }
			else
			{	int size = ptr->vectSize();
				cout << size <<" records found:" << endl;
			    for(int i = 0; i<size; i++)
			    {
			    	cout << i+1 << "\tFirst Name: " << ptr->getData()->at(i).getFname() << endl;
			    	cout << "\tLast Name: " << ptr->getData()->at(i).getLname() << endl;
			    	cout << "\tEmail: " << ptr->getData()->at(i).getEmail() << endl;
			    	cout << "\tPhone#: " << ptr->getData()->at(i).getPhone() << endl;
			    	cout << "\tCity: " << ptr->getData()->at(i).getCity() << endl;
			    	cout << "\tCountry: " << ptr->getData()->at(i).getCountry() << endl;
			    }
			}
			cout << endl;
		}	
		else if( command =="markfv") { myContactBST.markFav(myContactBST.getRoot(), key); cout << endl;}
		else if( command =="unmarkfv") { myContactBST.unmarkFav(myContactBST.getRoot(), key); cout << endl;}
		else if( command =="printASC") { myContactBST.printASC(myContactBST.getRoot()); cout << endl; }
		else if( command =="printDES") { myContactBST.printDES(myContactBST.getRoot()); cout << endl;}
		else if( command =="printfv") { myContactBST.printFav(myContactBST.getRoot()); cout << endl;}
		else if( command =="help") {listCommands(); cout << endl;}
		else if( command =="exit") {exit(-1);}
		else if( command == "") {continue;}
		else {cout <<"Invalid command !!!"<< endl; cout << endl;}
		cout<<">";
	}
  	return 0;
}
