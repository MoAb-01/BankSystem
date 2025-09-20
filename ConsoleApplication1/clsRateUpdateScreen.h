#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsRateUpdateScreen:protected clsScreen
{

	
public:
	static void ShowRateUpdateScreen()
	{
		system("cls");
		_PrintHeader("Update Currency Rate Screen");
		string currencyCode;
		float newRate;
		char choice;

		cout << "Please Enter Currency Code: ";
		currencyCode = clsInputValidate<string>::Read();
		clsCurrency myCurrency = clsCurrency::FindByCode(currencyCode);
		while (myCurrency.isEmpty())
		{
			cout << "Currency Not Found! Please Enter Valid Currency Code: ";
			currencyCode = clsInputValidate<string>::Read();
			myCurrency = clsCurrency::FindByCode(currencyCode);
		}

		cout << "Currency Card" << endl;
		myCurrency.Print();

		cout << endl << "Are You Sure You Want To Update This Currency Rate? [Y/N]: ";
		cin >> choice;

		if (toupper(choice) == 'Y')
		{
			cout << "Update Currency Rate:" << endl;
			cout << endl <<"________________________" << endl;
			cout << "Enter New Rate: ";
			newRate = clsInputValidate<double>::Read("Please Enter New Rate: ");
			myCurrency.UpdateRate(newRate);
			cout << "Currency Rate Updated Successfully!" << endl;
			myCurrency.Print();
		}
		else
		{
			cout << "Process Cancelled by the user!" << endl;
			return;
		}
	
	}

};

