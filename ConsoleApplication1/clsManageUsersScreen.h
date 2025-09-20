#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsUserAddScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindUserScreen.h"
class clsManageUsersScreen: protected clsScreen
{

    enum enManageUsersMenueOptions {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
    };


   static short _ReadManageUsersOption()
    {
		cout << "What Do You Want To Do 1-6? ";
		short number = clsInputValidate<short>::readNumberBetween(1, 6, "Enter Number Between 1-6");
        return number;
    }

    static void _GoBackToManageUsersMenue()
    {
        cout << "Press Any Key To Go TO Manage Users Menu...";
        system("pause>nul");
        ShowManageUsersMenue();
    }
    static void _ShowListUsersScreen()
    {
        clsListUsersScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        clsUserAddScreen::ShowAddUser();

    }

    static void _ShowDeleteUserScreen()
	{
        clsDeleteClientScreen::ShowDeleteClient();
	}

    static void _ShowUpdateUserScreen()
	{
        clsUpdateClientScreen::ShowUpdateClientScreen();

	}

    static  void _ShowFindUserScreen()
    {

        clsFindUserScreen::ShowFindUserScreen();
    }



    static void _PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
    {

        switch (ManageUsersMenueOption)
        {
        case enManageUsersMenueOptions::eListUsers:
        {
            system("cls");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eAddNewUser:
        {
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eDeleteUser:
        {
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eUpdateUser:
        {
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eFindUser:
        {
            system("cls");

            _ShowFindUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eMainMenue:
        {
            //do nothing here the main screen will handle it :-) ;
        }
        }

    }


public:
	static void ShowManageUsersMenue()
	{
		system("cls");
		_PrintHeader("Manage Users Screen");
		cout << setw(70) << "===========================================" << endl;
		cout << setw(30) << "\t\t\t\tManage Users" << endl;
		cout << setw(70) << "===========================================" << endl;
		cout << setw(50) << "[1] List Users." << endl;
		cout << setw(48) << "[2] Add New User." << endl;
		cout << setw(47) << "[3] Delete User." << endl;
		cout << setw(52) << "[4] Update User Info." << endl;
		cout << setw(45) << "[5] Find User." << endl;
		cout << setw(46) << "[6] Main Menu." << endl;
		_PerformManageUsersMenueOption(enManageUsersMenueOptions(_ReadManageUsersOption()));
	}
};

