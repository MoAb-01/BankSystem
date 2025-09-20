#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen :protected clsScreen
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
        cout << "\nUser Name   : " << User.getUserName();
        cout << "\nPassword    : " << User.getPassword();
        cout << "\nPermissions : " << User.getPermissions();
        cout << "\n___________________\n";

    }

public:
    static void ShowDeleteUserScreen()
    {
        if (hasRights(clsUser::enUserPermission::userEDeleteClient) == false)
        {
            return;
        }

        _PrintHeader("\tDelete User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate<string>::Read();
        while (!clsUser::isUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate<string>::Read();
        }

        clsUser User1 = clsUser::Find(UserName);
        _PrintUser(User1);

        cout << "\nAre you sure you want to delete this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            if (User1.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User1);
            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
    }

};
