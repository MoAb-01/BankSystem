#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;
class clsListCurrenciesScreen: protected clsScreen
{


	static void _PrintEachCurrency(clsCurrency currency)
	{
		cout << "| " << left<<setw(40) << currency.getCountry() << "| " <<left<< setw(6) << currency.getCurrencyCode() << "| " << left<<setw(35) << currency.getCurrencyName() << "|" << left<<setw(10) << currency.getRate()<<endl;

	}

public:

	static void ShowListCurrenciesScreen()
	{
		
		vector<clsCurrency> myvec = clsCurrency::GetCurrenciesList();
		_PrintHeader("Currencies List Scree", "(" + to_string(myvec.size()) + ") Currencies");
		cout << " ___________________________________________________________________________________________________________________" << endl;
		cout << "| " << left<<setw(40) << "Country" << "| " << left << setw(6) << "Code" << "| " <<left<<setw(35) << "Name" << "|" << left << setw(10) << "Rate/(1$)"<<endl;
		cout << " ___________________________________________________________________________________________________________________" << endl;
		if (myvec.size()==0)
		{
			cout << ":::::FILE IS EMPTY::::"<<endl;
		}
		else
		{
			for (clsCurrency& n : myvec)
			{
				_PrintEachCurrency(n);
			}
		}
		cout << " ___________________________________________________________________________________________________________________" << endl;
	}
};

