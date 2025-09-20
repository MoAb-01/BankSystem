#pragma once
#include<iostream>
#include<string>
using namespace std;

class clsPerson
{
private:
	string _firstName;
	string _lastName;
	string _fullName;
	string _phoneNumber;
	string _email;
	

public:
	clsPerson(string firstName,string lastName,string phoneNumber,string email)
	{
		_firstName = firstName;
		_lastName = lastName;
		_fullName = _firstName +" "+ _lastName;
		_phoneNumber = phoneNumber;
		_email = email;
	}

	void setFirstName(string firstName)
	{
		_firstName = firstName;
	}
	void setLastName(string lastName)
	{
		_lastName = lastName;
	}

	void setFullName(string firstName,string lastName)
	{
			_firstName = firstName;
			_lastName = lastName;
			_fullName = _firstName + " " + _lastName;  // ← ADD SPACE
	}
	
	void setPhoneNumber(string phonNumber)
	{
		_phoneNumber = phonNumber;
	}

	void setEmail(string email)
	{
		_email = email;
	}

	string getFirstName()
	{
		return _firstName;
	}

	string getLastName()
	{
		return _lastName;
	}

	string getFullName()
	{
		return _fullName;
	}

	string getEmail()
	{
		return _email;
	}

	string getPhoneNumber()
	{
		return _phoneNumber;
	}

	void Print()
	{
		cout << "Info:" << endl;
		cout << "_____________________________" << endl;
		cout << "First Name: " << _firstName << endl;
		cout << "Last Name: " << _lastName << endl;
		cout << "Phone Number: " << _phoneNumber << endl;
		cout << "Full Name: " << _fullName << endl;

		cout << "email: " << _email << endl;
		cout << "_____________________________" << endl;
	}

	

};

