#pragma once

#include <iostream>
#include <string>
#include "GlobalUser.h"
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsInputValidate.h"
#include "clsClientAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsShowTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsShowUsersRegisterScreen.h"
#include "clsShowCurrencyExchangeScreen.h"
class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenuOptions
	{
		eListClient=1,
		eAddNewClient=2,
		eDeleteClient=3,
		eUpdateClient=4,
		eFindClient=5,
		eShowTransactionsMenu=6,
		eManageUsers=7,
		eLoginRegister=8,
		eCurrencyExchange=9,
		eExit=10
	};

	static short _ReadMainMenuOptions()
	{
		cout << setw(66)<<"Choose What You Want To Do 1-10? ";
		short number = clsInputValidate<short>::readNumberBetween(1,10,"Enter Number Between 1-10");
		return number;
	}

	static  void _GoBackToMainMenu()
	{
		cin.clear();                // Clear error flags (if any)
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue... ";
		system("pause > nul");
		showMainMenu();
	}

	static void _ShowAllClientsScreen()
	{
		clsClientListScreen::ShowClientListScreen();

	}

	static void _ShowAddNewClientsScreen()
	{
		clsClientAddNewClientScreen::ShowAddNewClientScreen();

	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClient();

	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenu()
	{
		clsShowTransactionsScreen::ShowTransactionsScreen();
	}

	static void _ShowManageUsersMenue()
	{
		clsManageUsersScreen::ShowManageUsersMenue();
	}

	static void _Logout()
	{
		CurrentUser = clsUser::Find("", ""); //clear the object buffer
	}

	static void _ShowUserRegisterScreen()
	{
		system("cls");
		clsShowUsersRegisterScreen::ShowUsersRegisterScreen();
	}

	static void _ShowCurrencyExchangeScreen()
	{
		clsShowCurrencyExchangeScreen::ShowCurrencyExchangeScreen();
	}

	static void _ShowEndScreen()
	{
		/*cout << "\nEnd Screen Will be here...\n";*/

	}

	static void _perfromMainMenuOption(enMainMenuOptions choice)
	{
		switch (choice)
		{
			case enMainMenuOptions::eListClient:
			{
				system("cls");
				_ShowAllClientsScreen();
				_GoBackToMainMenu();
				break;
			}

			case enMainMenuOptions::eAddNewClient:
			{
				system("cls");
				_ShowAddNewClientsScreen();
				_GoBackToMainMenu();
				break;
			}

			case enMainMenuOptions::eDeleteClient:
			{
				system("cls");
				_ShowDeleteClientScreen();
				_GoBackToMainMenu();
				break;
			}

			case enMainMenuOptions::eUpdateClient:
			{
				system("cls");
				_ShowUpdateClientScreen();
				_GoBackToMainMenu();
				break;
			}

			case enMainMenuOptions::eFindClient:
			{
				system("cls");
				_ShowFindClientScreen();
				_GoBackToMainMenu();
				break;
			}

			case enMainMenuOptions::eShowTransactionsMenu:
			{
				system("cls");
				_ShowTransactionsMenu();
				_GoBackToMainMenu();
				break;
			}


			case enMainMenuOptions::eManageUsers:
			{
				system("cls");
				_ShowManageUsersMenue();
				_GoBackToMainMenu();
				break;
			}
			case enMainMenuOptions::eLoginRegister:
			{
				system("cls");
				_ShowUserRegisterScreen();
				_GoBackToMainMenu();
				break;
			}

			case enMainMenuOptions::eCurrencyExchange:
			{
				system("cls");
				_ShowCurrencyExchangeScreen();
				_GoBackToMainMenu();
			}
			case enMainMenuOptions::eExit:
			{
				system("cls");
				_Logout();
				break;
			}

				

		}
	}


public:
	void static showMainMenu()
	{
		system("cls");
		clsScreen::_PrintHeader("Main Screen");

		cout << setw(70) << "==========================================="<<endl;
		cout << setw(30) <<			"\t\t\t\tMain Menu" << endl;
		cout << setw(70) << "===========================================" << endl;
		cout << setw(50) << "[1] Show Client List." << endl;
		cout << setw(48) << "[2] Add New Client." << endl;
		cout << setw(47) << "[3] Delete Client." << endl;
		cout << setw(52) << "[4] Update Client Info." << endl;
		cout << setw(45) << "[5] Find Client." << endl;
		cout << setw(46) << "[6] Transactions." << endl;
		cout << setw(46) << "[7] Manage Users." << endl;
		cout << setw(48) << "[8] Login Register." << endl;
		cout << setw(51) << "[9] Currency Exchange." << endl;
		cout << setw(42) << "[10] Log Out." << endl;
		cout << setw(70) << "==========================================="<<endl;
		_perfromMainMenuOption(enMainMenuOptions(_ReadMainMenuOptions()));
	}
};

