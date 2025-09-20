#pragma once

#include <iostream>
#include <string>
#include <iomanip> // for std::setw
#include "GlobalUser.h"
#include "clsDate.h"
using namespace std;

class clsScreen
{


protected: 


	enum enUserPermission
	{
		usrEshowClientList = 1,
		userEAddNewClient = 2,
		userEDeleteClient = 3,
		userEUpdateClient = 4,
		userEFindClient = 5,
		userETransactions = 6,
		userEManageUsers = 7
	};

	static void _PrintTodaysDateAndUser()
	{
		cout << endl;
		cout << "\t\t\t\t\tUser:" << CurrentUser.getUserName() << endl;;
		cout << "\t\t\t\t\tDate:"<<clsDate::GetTodaysDate();
		cout << endl << endl;
	}

	static void _PrintHeader(string title,string subtitle="")
	{
		cout << setw(70) <<right<<"________________________________________" << endl<<endl;
		cout << "\t\t\t" << setw(35) << title << endl;
		if (subtitle != "")
		{
			cout << "\t\t\t" << setw(35) << subtitle << endl;
		}
		cout << setw(70) << "________________________________________" << endl<<endl;



		_PrintTodaysDateAndUser();
	}

	static bool hasRights(clsUser::enUserPermission permission)
	{
		if (CurrentUser.CheckAccessPermission(permission))
		{
			return true;
		}
		else
		{
			cout << "You Do not have the required permissions to do this action!" << endl;
			return false;
		}
	}
};

