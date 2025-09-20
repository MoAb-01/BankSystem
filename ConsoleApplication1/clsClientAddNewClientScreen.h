#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iostream>

class clsClientAddNewClientScreen:protected clsScreen //Lesson #9
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

		client.setFullName(client.getFirstName(), client.getLastName());
		cout << "Enter Pin Number: ";
		client.setPinCode(clsInputValidate<string>::Read());

		cout << "Enter Email: ";
		client.setEmail(clsInputValidate<string>::Read());
		cout << endl;

		cout << "Enter Phone number: ";
		client.setPhoneNumber(clsInputValidate<string>::Read());
		cout << endl;


		cout << "Enter ACcount Balance: ";
		client.setAccountBalance(clsInputValidate<double>::Read());
		cout << endl;
	}



	
public:
	static void ShowAddNewClientScreen()
	{
		_PrintHeader("Add New Client Screen");

		string accNo = clsInputValidate<string>::Read();
		while (clsBankClient::IsClientExist(accNo)) //dont add a clinet
		{
			cout << "Client Does exist, enter a different Account Number" << endl;
			accNo = clsInputValidate<string>::Read();
		}
		clsBankClient Client = clsBankClient::GetNewClientObject(accNo);
		_ReadClientInfo(Client);

		clsBankClient::enSaveResultsToFile SaveResult = Client.Save();

		switch (SaveResult)
		{
			case  clsBankClient::enSaveResultsToFile::svSucceed:
			{
				cout << "\nAccount Updated Successfully :-)\n";
				Client.Print();

				break;
			}
			case clsBankClient::enSaveResultsToFile::svFailedEmptyObject:
			{
				cout << "\nError account was not saved because it's Empty";
				break;

			}
		}
	}
};

