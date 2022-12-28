#include<iostream>
#include "contact.h"
#include <stdexcept>

using namespace std;

Contact::Contact()//default constructor
{
	this->fname = " ";
	this->lname = " ";
	this->email = " ";
	this->primaryPhone = " ";
	this->city = " ";
	this->country = " ";
	this->isFav = 0;
}
//constructor with arguments
Contact::Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav)
{
	this->fname = fname;
	this->lname = lname;
	this->email = email;
	this->primaryPhone = primaryPhone;
	this->city = city;
	this->country = country;
	this->isFav = isFav;
}

//getter functions
string Contact::getFname() { return(fname); }
string Contact::getLname() { return(lname); }
string Contact::getEmail() { return(email); }
string Contact::getPhone() { return(primaryPhone); }
string Contact::getCity() { return(city); }
string Contact::getCountry() { return(country); }
bool Contact::getIsFav() { return(isFav); }

//setter functions
void Contact::setFname(string first) { this->fname = first; }
void Contact::setLname(string last) { this->lname = last; }
void Contact::setEmail(string mail) { this->email = mail; }
void Contact::setPhone(string ph) { this->primaryPhone = ph; }
void Contact::setCity(string city) { this->city = city; }
void Contact::setCountry(string country) { this->country = country; }
void Contact::setIsFav(bool fav) { this->isFav = fav; }

void Contact::print()//helps to print the contact informations
{
	cout<<fname <<" "<<lname<<", "<<email<<", "<<primaryPhone<<", "<<city<<", "<<country<< ", " << isFav <<endl;
}	