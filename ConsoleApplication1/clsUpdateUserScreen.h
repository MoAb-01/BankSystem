#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen :protected clsScreen

{
private:


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

    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.setFirstName(clsInputValidate<string>::Read());

        cout << "\nEnter LastName: ";
        User.setLastName(clsInputValidate<string>::Read());

        cout << "\nEnter Email: ";
        User.setEmail(clsInputValidate<string>::Read());

        cout << "\nEnter Phone: ";
        User.setPhoneNumber(clsInputValidate<string>::Read());

        cout << "\nEnter Password: ";
        User.setPassword(clsInputValidate<string>::Read());

        cout << "\nEnter Permission: ";
        User.setPermissions(_ReadPermissionsToSet());
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

    static int _ReadPermissionsToSet()
    {
        int currPermissions = 0;
        char choice;
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
            currPermissions = currPermissions | enUserPermission::userEAddNewClient;
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
            currPermissions = currPermissions | enUserPermission::userEUpdateClient;
        }

        cout << "Find Client? y/n ";
        cin >> ws >> choice;
        if (toupper(choice) == 'Y')
        {
            currPermissions = currPermissions | enUserPermission::userEFindClient;
        }

        cout << "Transactions? y/n ";
        cin >> ws >> choice;
        if (toupper(choice) == 'Y')
        {
            currPermissions = currPermissions | enUserPermission::userETransactions;
        }

        cout << "Manage Users? y/n ";
        cin >> choice;
        if (toupper(choice) == 'Y')
        {
            currPermissions = currPermissions | enUserPermission::userEManageUsers;
        }

        return currPermissions;
    }

public:

    static void ShowUpdateUserScreen()
    {
        if (hasRights(clsUser::enUserPermission::userEUpdateClient) == false)
        {
            return;
        }

        _PrintHeader("\tUpdate User Screen");

        string UserName = "";

        cout << "\nPlease Enter User UserName: ";
        UserName = clsInputValidate<string>::Read();

        while (!clsUser::isUserExist(UserName))
        {
            cout << "\nAccount number is not found, choose another one: ";
            UserName = clsInputValidate<string>::Read();
        }

        clsUser User1 = clsUser::Find(UserName);

        _PrintUser(User1);

        cout << "\nAre you sure you want to update this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";


            _ReadUserInfo(User1);

            clsUser::enSaveResults SaveResult;

            SaveResult = User1.save();

            switch (SaveResult)
            {
            case  clsUser::enSaveResults::svSucceeded:
            {
                cout << "\nUser Updated Successfully :-)\n";

                _PrintUser(User1);
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError User was not saved because it's Empty";
                break;

            }

            }

        }

    }
};
