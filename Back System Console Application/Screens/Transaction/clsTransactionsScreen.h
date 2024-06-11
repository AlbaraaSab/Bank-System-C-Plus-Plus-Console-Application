#pragma once
#include <iomanip>
#include "../clsScreen.h"
#include "../clsMainScreen.h"
#include "../../Core/clsBankClient.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

class clsTransactionsScreen : protected clsScreen
{

private:
	enum enTransactionsMenueOptions
	{
		enDeposit = 1,
		enWithdrow = 2,
		enTotalBalances = 3,
		enTransfer = 4,
		enTransferLog = 5,
		enMainMenu = 6
	};

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrowScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalanceScreen::ShowTotalBalances();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _GoBackToTransactionsMenu()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Transcations Menu...\n";
		system("pause>0");
		ShowTransactionsMenu();
	}

	static short ReadTransactionsMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short option = clsInputValidate<short>::ReadNumberBetween(1, 6, "Enter Number between 1 to 6? ");
		return option;
	}

	static void _PerformTransactionsMenueOption(enTransactionsMenueOptions option)
	{
		switch (option)
		{
			case clsTransactionsScreen::enDeposit:
			{
				system("cls");
				_ShowDepositScreen();
				_GoBackToTransactionsMenu();
				break;
	
			}
			case clsTransactionsScreen::enWithdrow:
			{
				system("cls");
				_ShowWithdrowScreen();
				_GoBackToTransactionsMenu();
				break;
			}
			case clsTransactionsScreen::enTotalBalances:
			{
				system("cls");
				_ShowTotalBalancesScreen();
				_GoBackToTransactionsMenu();
				break;
			}
			case clsTransactionsScreen::enTransfer:
			{
				system("cls");
				_ShowTransferScreen();
				_GoBackToTransactionsMenu();
				break;
			}
			case clsTransactionsScreen::enTransferLog:
			{
				system("cls");
				_ShowTransferLogScreen();
				_GoBackToTransactionsMenu();
				break;
			}
			case clsTransactionsScreen::enMainMenu:
			{

			}
		}
	}


public:
	static void ShowTransactionsMenu()
	{
		system("cls");
		_DrawScreenHeader("Transactions Screen.");

		cout << setw(37) << left << "" << "===============================================\n";
		cout << setw(37) << left << "" << "\t\t   Transactoins Menu\n";
		cout << setw(37) << left << "" << "===============================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdrow.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
		cout << setw(37) << left << "" << "===============================================\n";
		
		_PerformTransactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
	}

};

