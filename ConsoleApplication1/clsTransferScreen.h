#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;



static vector<string> _loadTransferLog()
{
	vector<string> logData;
	fstream file("transferLog.txt", ios::in);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			logData.push_back(line);
		}
		file.close();
	}
	return logData;
}


static string _ConvertTransferInfoToLine(clsBankClient fromClient,clsBankClient toClient,float amount)
{

	return clsDate::GetTodaysDate() + "-" + clsTime::GetSystemTime() + "#//#" + fromClient.getAccountNumber() + "#//#" +
		toClient.getAccountNumber() + "#//#" + to_string(amount) + "#//#" + to_string(fromClient.GetAccountBalance()) + "#//#" + to_string(toClient.GetAccountBalance()) + "#//#" + CurrentUser.getUserName();
}
class clsTransferScreen :protected clsScreen
{


	static void _TransferLog(clsBankClient fromClient, clsBankClient toClient, float amount)
	{
		vector<string> _logData = _loadTransferLog();
		string line = _ConvertTransferInfoToLine(fromClient, toClient, amount);
		fstream file;
		file.open("transferLog.txt", ios::out | ios::app);
		if (file.is_open())
		{
			file << line << endl;
			file.close();
		}
	}

public:

	static void ShowTransferScreen()
	{ 
		_PrintHeader("Transactions", "Transfer Screen");
		cout << "Enter Account Number To Transfer From: ";
		string fromAccount = clsInputValidate<string>::Read();
		while (!clsBankClient::IsClientExist(fromAccount))
		{
			cout << "Client Does Not Exist, Enter a valid one" << endl;
			fromAccount = clsInputValidate<string>::Read();
		}
		clsBankClient fromClient = clsBankClient::Find(fromAccount);
		fromClient.Print();
		cout << "Enter Account Number To Transfer To: ";
		string toAccount = clsInputValidate<string>::Read();
		while (!clsBankClient::IsClientExist(toAccount))
		{
			cout << "Client Does Not Exist, Enter a valid one" << endl;
			toAccount = clsInputValidate<string>::Read();
		}
		clsBankClient toClient = clsBankClient::Find(toAccount);
		toClient.Print();
		cout << "Enter Amount To Transfer To? ";
		double amount = clsInputValidate<double>::Read("Enter Amount To Transfer? ");
		if (fromClient.Transfer(amount, toClient))
		{

			char choice;
			cout << "Are You Sure You Want To Transfer " << amount << " From Account Number: " << fromAccount
				<< " To Account Number: " << toAccount << " Y/N? ";
			cin >> choice;

			if (toupper(choice) == 'Y')
			{
				fromClient.Withdraw(amount);
				toClient.Deposit(amount);
				cout << "Transfer Completed Successfully!" << endl;
				fromClient.Print();
				toClient.Print();
				_TransferLog(fromClient, toClient, amount);
			}
			else
			{
				cout << "Process Is Canccelled By User!" << endl;
				return;
			}


		}
		else
		{
			cout << "Transfer Failed! Insufficient Balance!" << endl;
			return;
		}
		
		
		
	}
};

