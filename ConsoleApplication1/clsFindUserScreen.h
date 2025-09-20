#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen :protected clsScreen
{

private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.getFirstName();
        cout << "\nLastName    : " << User.getLastName();
        cout << "\nFull Name   : " << User.getFullName();
        cout << "\nEmail       : " << User.getEmail();
        cout << "\nPhone       : " << User.getPhoneNumber();
        cout << "\nUserName    : " << User.getUserName();
        cout << "\nPassword    : " << User.getPassword();
        cout << "\nPermissions : " << User.getPermissions();
        cout << "\n___________________\n";

    }

public:

    static void ShowFindUserScreen()
    {
        if (hasRights(clsUser::enUserPermission::userEFindClient) == false)
        {
            return;
        }

        _PrintHeader("\t  Find User Screen");

        string UserName;
        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate<string>::Read();
        while (!clsUser::isUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate<string>::Read();
        }

        clsUser User1 = clsUser::Find(UserName);

        if (!User1.isEmpty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";
        }

        _PrintUser(User1);

    }

};
