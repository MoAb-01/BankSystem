#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h" // Ensure this header is included
#include "clsTransferLogScreen.h"
using namespace std;

class clsShowTransactionsScreen :protected clsScreen
{
    enum enTransactionsMenuOptions {
        eDeposit = 1, eWithdraw = 2,
        eShowTotalBalance = 3,eTransfer=4, eTransferLog=5,eShowMainMenue = 6
    };

    static short _ReadTransactionChoice()
    {
        cout << "Choose What you Want To Do 1-6.. ";
		short choice = clsInputValidate<short>::readNumberBetween(1, 6, "Enter Number Between 1-6");
        return choice;
    }

    static void _GoBackToTransactionsMenu()
    {
        cout << "Press Any Key To Go Back To Transactions Menu...";
        system("pause>nul");
        ShowTransactionsScreen();
    }


    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }
	static void _ShowWithdrawScreen()
	{
        clsWithdrawScreen::ShowWithdrawScreen();
    }
	static void _ShowTotalBalancesScreen()
	{
        clsTotalBalancesScreen::ShowTotalBalancesScreen();
    }
    static void  _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }
    static void _ShowTransferLogScreen()
    {
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    static void _PerfromTransactionsMenuOption(enTransactionsMenuOptions ChTransaction)
    {
        switch (ChTransaction)
        {
		    case enTransactionsMenuOptions::eDeposit:
		    {
                system("cls");
			    _ShowDepositScreen();
                _GoBackToTransactionsMenu();
			    break;
		    }
			case enTransactionsMenuOptions::eWithdraw:
			{
                system("cls");
				_ShowWithdrawScreen();
				_GoBackToTransactionsMenu();
				break;
			}
			case enTransactionsMenuOptions::eShowTotalBalance:
			{
                system("cls");
				_ShowTotalBalancesScreen();
				_GoBackToTransactionsMenu();
				break;
			}
			case enTransactionsMenuOptions::eTransfer:
			{
                system("cls");
                _ShowTransferScreen();
				_GoBackToTransactionsMenu();
                break;
			}
            case enTransactionsMenuOptions::eTransferLog:
            {
                system("cls");
                _ShowTransferLogScreen();
                _GoBackToTransactionsMenu();
                break;
            }
			case enTransactionsMenuOptions::eShowMainMenue:
			{
				
			}

        }
    }
public:
    static void ShowTransactionsScreen()
    {
		system("cls");
		_PrintHeader("Transactions Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerfromTransactionsMenuOption( enTransactionsMenuOptions(_ReadTransactionChoice()));
    }
};

