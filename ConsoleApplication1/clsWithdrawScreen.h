#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iostream>


class clsWithdrawScreen : protected clsScreen
{
public:
	static void ShowWithdrawScreen()
	{
		cout << "Enter Account Number: ";
		string accountNumber = clsInputValidate<string>::Read();;

		while (!clsBankClient::IsClientExist(accountNumber))
		{
			cout << "Client Does Not Exist, Enter a valid one" << endl;
			accountNumber = clsInputValidate<string>::Read();;
		}

		clsBankClient client = clsBankClient::Find(accountNumber);
		client.Print();
		double amount;
		cout << "Enter Amount To Withdraw: ";
		amount = clsInputValidate<double>::Read("Enter Amount To Withdraw: ");
		char choice;
		cout << "Are You Sure You Want To Withdraw " << amount << " From Account Number: " << accountNumber << " Y/N? ";
		cin >> choice;

		if (toupper(choice) == 'Y')
		{
			if (client.Withdraw(amount))
			{
				cout << "Withdraw Completed Successfully!" << endl << "New Balance Is: " << client.GetAccountBalance() << endl;
			}
			else
			{
				cout << "Withdraw Amount entered is either zero or negative or more than the balance" << endl;
				cout << "Your Withdraw Amount is " << amount << endl << "Your Balance Is " << client.GetAccountBalance() << endl;
			}
		}
		else
		{
			cout << "Process Is Canccelled By User!" << endl;
		}
	}
};

