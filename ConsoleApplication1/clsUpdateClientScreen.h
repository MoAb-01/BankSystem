#pragma once

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iostream>


class clsUpdateClientScreen:clsScreen
{

private:
	static void _ReadClientInfo(clsBankClient& client)
	{
		cout << "Enter FirstName: ";
		client.setFirstName(clsInputValidate<string>::Read());
		cout << endl;

		cout << "Enter Last Name: ";
		client.setLastName(clsInputValidate<string>::Read());
		cout << endl;
		cout << "Enter Phone number: ";
		client.setPhoneNumber(clsInputValidate<string>::Read());
		cout << endl;

		cout << "Enter Email: ";
		client.setEmail(clsInputValidate<string>::Read());
		cout << endl;

		cout << "Enter Pin Number: ";
		client.setPinCode(clsInputValidate<string>::Read());
		cout << endl;

		cout << "Enter Account Balance: ";
		client.setAccountBalance(clsInputValidate<double>::Read("Enter Balance:"));
		cout << endl;
	}

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
	static void ShowUpdateClientScreen()
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
		_PrintClient(client);
		char n;
		cout << "Are You Sure You Want To Update This Client? Y/N ";
		cin >> n;

		if(toupper(n)=='Y')
		{
			_ReadClientInfo(client);
			clsBankClient::enSaveResultsToFile sv = client.Save();
			if (sv == clsBankClient::enSaveResultsToFile::svSucceed)
			{
				cout << "Client Update Completed :-)" << endl;
				_PrintClient(client);
			}
			else if (sv == clsBankClient::enSaveResultsToFile::svFailedEmptyObject())
			{
				cout << "Client Update Failed.. Empty Object" << endl;
			}
		}
		

		
		

	}


};

