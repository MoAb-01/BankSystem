#pragma once

#include<iostream>
#include "clsBankClient.h"
#include "clsClientListScreen.h"
#include "clsUtil.h"
#include "clsScreen.h"

class clsTotalBalancesScreen:protected clsScreen
{
public:
	static void ShowTotalBalancesScreen()
	{
		_PrintHeader("Total Balances Screen");
		clsClientListScreen::ShowClientListScreen();
		cout << endl; 
		cout << "\t\t\t\t Total Balances: " << clsBankClient::getTotalBalances() << endl;
		cout << "\t\t\t\t (" << clsUtil::NumberToText(clsBankClient::getTotalBalances()) << ")" << endl;
	}
};

