#pragma once
#include<iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsDepositScreen:protected clsScreen
{
public:
	static void ShowDepositScreen()
	{
		_PrintHeader("Deposit Screen");

		cout << "Enter Account Number: ";
		string accountNumber= clsInputValidate<string>::Read();
		if (!clsBankClient::IsClientExist(accountNumber))
		{
			cout << "Enter A valid Account Number: ";
			accountNumber = clsInputValidate<string>::Read();
		}
		clsBankClient client = clsBankClient::Find(accountNumber); 
		client.Print();
		cout << endl;
		double amount;
		cout << "Enter Amount To Deposit: ";
		cin >> amount;

	
		char choice;
		cout << "Are You Sure You Want To Deposit " << amount << " To Account Number: " << accountNumber << " Y/N? ";
		cin >> choice;

		if (toupper(choice) =='Y')
		{
			if(client.Deposit(amount))
			{
				cout << "Deposit Completed Successfully!" << endl << "New Balance Is: " << client.GetAccountBalance() << endl;
			}
			else
			{
				cout << "Deosit Amount entered is either zero or negative..Process Terminated!" << endl;
			}
		}
		else
		{
			cout << "Process Is Canccelled By User!" << endl;
		}	
	}
};

