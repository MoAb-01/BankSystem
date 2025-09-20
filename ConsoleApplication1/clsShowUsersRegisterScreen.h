#pragma once

#include "clsScreen.h"
#include "clsString.h"
#include "clsDate.h"
class clsShowUsersRegisterScreen : protected clsScreen
{
private:

	static vector<string> _loadLoginRegister()
	{
		vector<string> myvec;
		fstream file("loginRegister.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				myvec.push_back(line);
			}
			file.close();
		}
		return myvec;
	}

	static void _PrintEachUserInfo()
	{
		vector<string> myvec = _loadLoginRegister();
		for (string& n : myvec)
		{
			vector<string> user = clsString::split(n, "#//#");
			cout << setw(2) << "| " << setw(20) << left << user[0]
				<< "| " << setw(20) << left << user[1]
				<< "| " << setw(20) << left << user[2]
			    << "| " << setw(20) << left << user[3]<<endl;
		}
	}
public:
	static void ShowUsersRegisterScreen()
	{
		if (hasRights(clsUser::enUserPermission::userELoginRegister) == false)
		{
			return;
		}

		vector<string> myvec = _loadLoginRegister();
		_PrintHeader("Login Register List Screen","("+to_string(myvec.size())+") Record(s)");

		cout << setw(10) << left << "__________________________________________________________________________________________" << endl;
		cout << setw(2) << "| " << setw(20) << left << "Date & Time"
			<< "| " << setw(20) << left << "User Name"
			<< "| " << setw(20) << left << "Password"
			<< "| " << setw(10) << left << "Permissions"
			<< "|" << endl;
		cout << setw(10) <<left<< "__________________________________________________________________________________________" << endl;
		_PrintEachUserInfo();
		cout << setw(10) << left << "__________________________________________________________________________________________" << endl;
	}
};

