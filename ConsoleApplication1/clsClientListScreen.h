#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
class clsClientListScreen:protected clsScreen //Lesson #8
{


private:
	static void _printClientRecordLine(clsBankClient n)
	{
		cout << setw(8) << left << "" << "| " << setw(13) << left << n.getAccountNumber();
		cout << "| " << setw(15) << left << n.getFullName();
		cout << "| " << setw(15) << left << n.getPhoneNumber();
		cout << "| " << setw(25) << left << n.getEmail();
		cout << "| " << setw(15) << left << n.getPinCode();
		cout << "| " << setw(15) << left << n.GetAccountBalance();
		cout << endl;
	}

public:
	static void ShowClientListScreen()
	{
		vector<clsBankClient> myvec = clsBankClient::getClientsList();
		_PrintHeader("Client List Screen",to_string(myvec.size())+" client(s)"); //from clsScreen.h
		cout << setw(8)<< "" <<" ____________________________________________________________________________________________________" << endl << endl;
		cout << setw(8)<<""<<"|" << setw(8) << left << "AccountNumber ";
		cout << "| " << setw(15) << left << "Client Name";
		cout << "| " << setw(15) << left << "Phone Number";
		cout << "| " << setw(25) << left << "Email";
		cout << "| " << setw(15) << left << "Pin Code";
		cout << "| " << setw(15) << left << "Balance";
		cout << endl;
		cout << setw(8) << "" << " ____________________________________________________________________________________________________" << endl << endl;

		if (myvec.size() == 0)
		{
			cout << "\t\t\tNO CLIENTS TO SHOW" << endl;
		}
		else
		{
			for (clsBankClient& n : myvec)
			{
				_printClientRecordLine(n);
			}
		}
		cout << setw(8) << "" << " ____________________________________________________________________________________________________" << endl << endl;

	}
};

