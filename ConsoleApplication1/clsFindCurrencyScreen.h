#pragma once
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "string.h"
#include "clsScreen.h"
class clsFindCurrencyScreen :protected clsScreen
{
	enum enFindBy { Code = 1, Country = 2 };
	static void _ShowResult(clsCurrency myCurrency)
	{
		if (!myCurrency.isEmpty())
		{
			cout << "Currency Found!" << endl;
			myCurrency.Print();
		}
		else
		{
			cout << "Currency Not Found!" << endl;
			return;
		}
	}
public:
	static void ShowFindCurrencyScreen()
	{
		_PrintHeader("Find Currency Screen");
		cout << "Find By: [1] Currency Code [2] Country: ";
		short choice = clsInputValidate<short>::readNumberBetween(1, 2, "Enter 1 or 2");
		string input;
		switch (choice)
		{
			case enFindBy::Code:
			{
				cout << "Please Enter Currency Code: ";
				input = clsInputValidate<string>::Read();
				clsCurrency myCurrency = clsCurrency::FindByCode(input);
				_ShowResult(myCurrency);
				break;
			}

			case enFindBy::Country:
			{
				cout << "Please Enter Currency Country: ";
				input = clsInputValidate<string>::Read();
				clsCurrency myCurrency = clsCurrency::FindByCountry(input);
				_ShowResult(myCurrency);
				break;
			}
			
		}
		
	}
	
};

