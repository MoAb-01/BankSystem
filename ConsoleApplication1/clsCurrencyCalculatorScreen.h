#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsString.h"
#include "clsInputValidate.h"
using namespace std;
class clsCurrencyCalculatorScreen:protected clsScreen
{


	static clsCurrency _ReadCurrency( int number)
	{
		cout << "Please Enter Currency"<<number<<" Code:";
		string currencyCode = clsInputValidate<string>::Read();
		clsCurrency currency = clsCurrency::FindByCode(currencyCode);

		while (currency.isEmpty())
		{
			cout << "Currency Code is not found please retry: ";
			currencyCode = clsInputValidate<string>::Read();
			currency = clsCurrency::FindByCode(currencyCode);
		}
		return currency;
	}

	static bool _CheckCurrenciesSame(long long amount,clsCurrency currency1, clsCurrency currency2)
	{
		if (clsCurrency::isCurrenciesSame(currency1, currency2)) //EGP EGP 
		{
			cout << "Currencies are the same, no conversion needed." << endl;
			currency1.Print();
			cout << amount << " " << currency1.getCurrencyCode() << " = " << amount << " " << currency2.getCurrencyCode() << endl;
			return true;
		}
		return false;
	}
public: 
	static void ShowCurrencyCalculatorScreen()
	{
		char choice;
		do
		{
			system("cls");
			_PrintHeader("Currency Calculator Screen");
			clsCurrency currency1 = _ReadCurrency(1);
			clsCurrency currency2 = _ReadCurrency(2);

			cout << "Enter Amount To Exchange: ";
			double amount = clsInputValidate<long>::Read("invalid! please try again..");
			double amountInUSD = amount;
			
			if (_CheckCurrenciesSame(amount,currency1,currency2))
			{
				return;
			}

			cout << "Convert From: " << endl;
			currency1.Print();

			if (!currency1.isUSD())
			{
				amountInUSD = currency1.ConvertFromCurrencyToUSD(amount);
				cout << amount << currency1.getCurrencyCode() << " = " << amountInUSD << "USD" <<endl;
			}
			cout << "Converting From USD To:"<<endl;
			currency2.Print();
			cout << amount << " " << currency1.getCurrencyCode() << " = " << currency2.ConvertFromUSDToCurrency(amountInUSD) << " "<<currency2.getCurrencyCode()<< endl;
			cout << "Do u want to perform another operation? Y/N: ";
			choice = clsInputValidate<char>::Read();
		} while (toupper(choice) != 'N');
		
		
	}
};

