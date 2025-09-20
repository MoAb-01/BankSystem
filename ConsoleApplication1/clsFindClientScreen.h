#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include <iostream>
using namespace std;

class clsFindClientScreen: public clsScreen
{
	static void _PrintClient(clsBankClient& Client)
	{
		cout << "Client Card:" << endl;
		cout << "______________________" << endl;
		cout << "First Name: " << Client.getFirstName() << endl;
		cout << "Last Name: " << Client.getLastName() << endl;
		cout << "Full Name:" << Client.getFullName() << endl;
		cout << "Email: " << Client.getEmail() << endl;
		cout << "Phone Number: " << Client.getPhoneNumber() << endl;
		cout << "Account Number: " << Client.getAccountNumber() << endl;
		cout << "Password: " << Client.getPinCode() << endl;
		cout << "Balance: " << Client.GetAccountBalance() << endl;
		cout << "______________________" << endl;
	}

public:
	static void ShowFindClientScreen()
	{
		_PrintHeader("Update Client Screen");
		cout << "Enter Account Number: ";
		string accountNumber = clsInputValidate<string>::Read();
		while (!clsBankClient::IsClientExist(accountNumber))
		{
			cout << "Client Does Not Exist.. Enter Valid Account Number: ";
			accountNumber = clsInputValidate<string>::Read();
		}

		clsBankClient client = clsBankClient::Find(accountNumber);

		if (!client.IsEmpty())
		{
			cout << "Client Found.." << endl;
			_PrintClient(client);
		}
		cout << "Client Is Not Found";

	}


};

