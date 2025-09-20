#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "GlobalUser.h"
class clsUserAddScreen: protected clsScreen
{
	

	
	static int _ReadUserPermissions()
	{

		int currPermissions = 0;
		char choice;

		cout << "Do you want to give full access to the system ? ";
		cin >> choice;
		if (toupper(choice) == 'Y')
		{
			return -1;
		}
		cout << "Do you want to give to: " << endl;
		cout << "Show Client List? y/n ";
		cin >> ws >> choice;

		if (toupper(choice) == 'Y')
		{
			currPermissions = currPermissions | enUserPermission::usrEshowClientList;

		}


		cout << "Add New Client? y/n ";
		cin >> ws >> choice;
		if (toupper(choice) == 'Y')
		{
			currPermissions = currPermissions | enUserPermission::userEAddNewClient; userEAddNewClient;
		}

		cout << "Delete Client? y/n ";
		cin >> ws >> choice;
		if (toupper(choice) == 'Y')
		{
			currPermissions = currPermissions | enUserPermission::userEDeleteClient;
		}

		cout << "Update Client? y/n ";
		cin >> ws >> choice;
		if (toupper(choice) == 'Y')
		{
			currPermissions = currPermissions | clsUser::enUserPermission::userEUpdateClient;
		}

		cout << "Find Client? y/n ";
		cin >> ws >> choice;
		if (toupper(choice) == 'Y')
		{
			currPermissions = currPermissions | clsUser::enUserPermission::userEFindClient;
		}

		cout << "Transactions? y/n ";
		cin >> ws >> choice;
		if (toupper(choice) == 'Y')
		{
			currPermissions = currPermissions | clsUser::enUserPermission::userETransactions;
		}

		cout << "Manage Users? y/n ";
		cin >> choice;
		if (toupper(choice) == 'Y')
		{
			currPermissions = currPermissions | clsUser::enUserPermission::userEManageUsers;
		}

		cout << "Show Login Register ? y/n ";
		cin >> choice;
		if (toupper(choice) == 'Y')
		{
			currPermissions = currPermissions | clsUser::enUserPermission::userELoginRegister;
		}
		return currPermissions;
	}


	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter FirstName: ";
		User.setFirstName(clsInputValidate<string>::Read());

		cout << "\nEnter LastName: ";
		User.setLastName(clsInputValidate<string>::Read());

		User.setFullName(User.getFirstName(), User.getLastName());

		cout << "\nEnter Email: ";
		User.setEmail(clsInputValidate<string>::Read());

		cout << "\nEnter Phone: ";
		User.setPhoneNumber(clsInputValidate<string>::Read());

		cout << "\nEnter Password: ";
		User.setPassword(clsInputValidate<string>::Read());

		cout << "\nEnter Permission: ";
		User.setPermissions(_ReadUserPermissions());
	}

	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.getFirstName();
		cout << "\nLastName    : " << User.getLastName();
		cout << "\nFull Name   : " << User.getFullName();
		cout << "\nEmail       : " << User.getEmail();
		cout << "\nPhone       : " << User.getPhoneNumber();
		cout << "\nUser Name   : " << User.getUserName();
		cout << "\nPassword    : " << User.getPassword();
		cout << "\nPermissions : " << User.getPermissions();
		cout << "\n___________________\n";

	}

public:
	static void ShowAddUser()
	{

		if (hasRights(clsUser::enUserPermission::userEAddNewClient) == false)
		{
			return;
		}

		system("cls");
		_PrintHeader("Manage Users","Add New User Screen");
		cout << "Enter Username: ";
		string username = clsInputValidate<string>::Read();
		while (clsUser::isUserExist(username))
		{
			cout << "Username already exist, enter a unique username ";
			username = clsInputValidate<string>::Read();
		}

		clsUser user = clsUser::GetAddNewUserObject(username);

		_ReadUserInfo(user);

		cout << "Are you sure you want to add this user? Y/n ";
		char choice;
		cin >> choice; 
		if (toupper(choice) == 'Y')
		{
			clsUser::enSaveResults svRes = user.save();

			switch (svRes)
			{
			case clsUser::enSaveResults::svSucceeded:
			{
				cout << "Saved Successfully! " << endl;
				_PrintUser(user);
				break;
			}
			case clsUser::enSaveResults::svFaildEmptyObject:
			{
				cout << "\nError User was not saved because it's Empty";
				break;

			}
			case clsUser::enSaveResults::svFaildUserExists:
			{
				cout << "\nError User was not saved because UserName is used!\n";
				break;

			}
			}
		}
	}

};

