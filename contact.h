#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>
using namespace std;

class Contact
{
	private:
		std::string fname;
		std::string lname;
		std::string email;
		std::string primaryPhone;
		std::string city;
		std::string country;
		bool isFav;

	public:
		Contact();//constructor with no arguments
		Contact(std::string fname, std::string lname, std::string email, std::string primaryPhone,
		 std::string city, std::string country, bool isFav); //constructor with arguments

		//getter functions 
		std::string getFname();
		std::string getLname();
		std::string getEmail();
		std::string getPhone();
		std::string getCity();
		std::string getCountry();
		bool getIsFav();

		//setter functions
		void setFname(std::string first);
		void setLname(std::string last);
		void setEmail(std::string mail);
		void setPhone(std::string ph);
		void setCity(std::string city);
		void setCountry(std::string country);
		void setIsFav(bool fav);

		void print();//prints the contact informations	
};

#endif