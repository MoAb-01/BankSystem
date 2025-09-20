#pragma once

#include <string>
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDeleteClientScreen
{

private:
	static void _PrintClient(clsBankClient& Client)
	{
		cout << "Client Card:" << endl;
		cout << "______________________" << endl;
		cout << "First Name: " << Client.getFirstName() << endl;
		cout << "Last Name: " << Client.getLastName() << endl;
		cout << "Full Name:" << Client.getFullName() << endl;
		cout << "Email: " << Client.getEmail() << endl;
		cout << "Account Number: " << Client.getAccountNumber() << endl;
		cout << "Password: " << Client.getPinCode() << endl;
		cout << "Balance: " << Client.GetAccountBalance() << endl;
		cout << "______________________" << endl;
	}

public:
	static void ShowDeleteClient() //# Lesson #4
	{
		cout << "Enter Account Number: ";
		string accountNumber = clsInputValidate<string>::Read();
		while (!clsBankClient::IsClientExist(accountNumber))
		{
			cout << "Client Does Not Exist, Enter a valid one" << endl;
			accountNumber = clsInputValidate<string>::Read();
		}

		clsBankClient client = clsBankClient::Find(accountNumber);

		_PrintClient(client);

		char n;
		cout << "\n\nAre You Sure You Want To Delete This Client Y/N ";
		n = clsInputValidate<char>::Read();

		if (toupper(n) == 'Y')
		{
			client.DeleteClient();
			cout << "Client Deleted Successfully!";
			_PrintClient(client);

		}
	}

};

