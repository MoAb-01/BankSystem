#pragma once

#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsRateUpdateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
class clsShowCurrencyExchangeScreen:public clsScreen
{

	enum enCurrenyMenu{List=1, Find=2, Update=3,Calculator=4,MainMenu=5};


	static int _ReadMainMenuOption()
	{
		cout<< "Choose What You Want To Do 1-5? ";
		int number = clsInputValidate<short>::readNumberBetween(1, 5, "Enter Number Between 1-5");
		return number;
	} 

	static void _GoBackToCurrencyExchangeMenu()
	{
		cout << "Press Any Key To Return To Currency Exchange Menu";
		system("pause>0");
		ShowCurrencyExchangeScreen();
	}

	static void _ListCurrenciesScreen()
	{
		clsListCurrenciesScreen::ShowListCurrenciesScreen();
	}

	static void _FindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void CurrencyRateUpdateScreen()
	{
		clsRateUpdateScreen::ShowRateUpdateScreen();
	}

	static void _CurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}




	static void _PerformMainMenuOptions(enCurrenyMenu choice)
	{
		switch (choice)
		{
		case enCurrenyMenu::List:
			system("cls");
			_ListCurrenciesScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		case enCurrenyMenu::Find:
			system("cls");
			_FindCurrencyScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		case enCurrenyMenu::Update:
			system("cls");
			CurrencyRateUpdateScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		case enCurrenyMenu::Calculator:
			system("cls");
			_CurrencyCalculatorScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		case enCurrenyMenu::MainMenu:
			system("cls");
			_GoBackToCurrencyExchangeMenu(); //go back to main menu
			break;
		}
	}

public:
	static void ShowCurrencyExchangeScreen()
	{
		system("cls");
		_PrintHeader("Currency Exchange Main Menu");


		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Currency Exhange Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_PerformMainMenuOptions(enCurrenyMenu(_ReadMainMenuOption()));
	}

	
	
};

