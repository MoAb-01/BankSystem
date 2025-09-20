#pragma once
#include <thread>
#include <chrono>
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "GlobalUser.h"

using namespace std;
class clsLogin : protected clsScreen
{

public:
	static bool Login()
	{
		

		system("cls");
		_PrintHeader("xxxx Login Screen xxxx");
		bool loginFailed = false;
		string username;
		string password;
		int count = 0;
		do
		{

			cout << "Enter Username: ";
			username = clsInputValidate<string>::Read();
			cout << "Enter password: ";
			password = clsInputValidate<string>::Read();

			CurrentUser = clsUser::Find(username, password);
			if (CurrentUser.isEmpty())
			{
				loginFailed = true;
				cout << "login failed.. "<<2-count <<" Trials Left" << endl;
				count++;
			}
			else
			{
				loginFailed = false;
			}
			if (count == 3)
			{
				cout << "You're Locked Due To Entering Password More Than Three Times....";
				return false;
			}
		} while (loginFailed == true);

		CurrentUser.StoreUserRegisterInfo();
		clsMainScreen::showMainMenu();
		
	}
};

