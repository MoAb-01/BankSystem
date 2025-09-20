#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;
class clsTransferLogScreen:protected clsScreen
{



	static void _printEachLogRecord(string logLine)
	{
		vector<string> myvec = clsString::split(logLine,"#//#");

		cout << "|" << setw(18) << myvec[0] << "|" << setw(15) << myvec[1] << "|" << setw(15) << myvec[2] << "|" << setw(15) << myvec[4] << setw(15) << myvec[5] << "|" << setw(8) << myvec[6] << "|" << endl;
	}
public:
	static void ShowTransferLogScreen()
	{
		_PrintHeader("Transfer Log Screen");
		cout << "__________________________________________________________________________________________________" << endl;
		cout << "|" << setw(18) << "Date/Time" << "|" << setw(15) << "f.account" << "|" << setw(15) << "t.account" << "|" << setw(15) << "s.balance" << setw(15) << "t.balance" << "|" << setw(8) << "User" << "|" << endl;
		cout << "__________________________________________________________________________________________________" << endl;


		vector<string> vLoad = clsBankClient::_loadTransferLog();

		if (vLoad.size() == 0)
		{
			cout << "\n\n NO LOGS FOUND!" << endl;
		}
		else
		{
			for (string& logLine : vLoad)
			{
				_printEachLogRecord(logLine);
			}
		}
		cout << "__________________________________________________________________________________________________" << endl;
	}
	
};

