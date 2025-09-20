#pragma once
#include "clsInputValidate.h"
#include "clsUser.h"

class clsLoginScreen
{
public:
	void ShowLoginScreen()
	{
		bool loginFailed;
		do
		{
			string username = clsInputValidate::ReadString();
			string password = clsInputValidate::ReadString();

			clsUser currentUser = clsUser::Find(username, password);
			
			
		}
	}
	
};

