#pragma once
#include <iomanip>
#include "../Core/Global.h"
#include "../Core/clsUser.h"
#include "clsScreen.h"
#include "../Libs/clsInputValidate.h"
#include "../Screens/Client/clsClientsListScreen.h"
#include "../Screens/Client/clsAddNewClientScreen.h"
#include "../Screens/Client/clsDeleteClientScreen.h"
#include "../Screens/Client/clsUpdateClientScreen.h"
#include "../Screens/Client/clsFindClientScreen.h"
#include "../Screens/Transaction/clsTransactionsScreen.h"
#include "../Screens/User/clsManageUsersScreen.h"
#include "../Screens/Login/clsLoginRegisterScreen.h"
#include "../Screens/Currency/clsCurrencyExchangeMenuScreen.h"

class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenuOptions
	{
		ShowClientsList = 1,
		AddNewClient = 2,
		DeleteClient = 3,
		UpdateClientInfo = 4,
		FindClient = 5,
		Transactions = 6,
		ManageUsers = 7,
		LoginRegister = 8,
		CurrencyExchange = 9,
		Logout = 10
	};

	static short _ReadMainMenuOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
		short option = clsInputValidate<short>::ReadNumberBetween(1, 10, "Enter Number between 1 to 10? ");
		return option;
	}

	static void _ShowClientListScreen()
	{
		if (!CurrentUser.CheckAccessPermission(clsUser::pListClient))
		{
			clsScreen::_ShowAccessDeniedMessage();
			_GoBackToMainMenu();
		}

		clsClientsListScreen::ShowClientsListScreen();
	}

	static void _AddNewClientScreen()
	{
		if (!CurrentUser.CheckAccessPermission(clsUser::pAddCLient))
		{
			clsScreen::_ShowAccessDeniedMessage();
			_GoBackToMainMenu();
		}

		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _DeleteClientScreen()
	{
		if (!CurrentUser.CheckAccessPermission(clsUser::pDeleteClient))
		{
			clsScreen::_ShowAccessDeniedMessage();
			_GoBackToMainMenu();
		}

		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _UpdateClientInfoScreen()
	{
		if (!CurrentUser.CheckAccessPermission(clsUser::pUpdateClient))
		{
			clsScreen::_ShowAccessDeniedMessage();
			_GoBackToMainMenu();
		}

		clsUpdateClientScreen::ShowUpdateClientScreen();
	}
	
	static void _FindClientScreen()
	{
		if (!CurrentUser.CheckAccessPermission(clsUser::pFindClient))
		{
			clsScreen::_ShowAccessDeniedMessage();
			_GoBackToMainMenu();
		}

		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenu()
	{
		if (!CurrentUser.CheckAccessPermission(clsUser::pTransactions))
		{
			clsScreen::_ShowAccessDeniedMessage();
			_GoBackToMainMenu();
		}

		clsTransactionsScreen::ShowTransactionsMenu();
	}

	static void _ShowManageUsersMenu()
	{
		if (!CurrentUser.CheckAccessPermission(clsUser::pManageUsers))
		{
			clsScreen::_ShowAccessDeniedMessage();
			_GoBackToMainMenu();
		}

		clsManageUsersScreen::ShowManageUsersMenu();
	}

	static void _ShowLogInRegisterScreen()
	{
		if (!CurrentUser.CheckAccessPermission(clsUser::pLoginRegister))
		{
			clsScreen::_ShowAccessDeniedMessage();
			_GoBackToMainMenu();
		}

		clsLoginRegisterScreen::ShowLogInRegisterScreen();
	}

	static void _ShowCurrencyExchangeScreen()
	{
		clsCurrencyExchangeMenuScreen::ShowCurrencyExChangeMenu();
	}

	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static void _GoBackToMainMenu()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
		system("pause>0");
		ShowMainMenu();
	}

	static void _GoBackToMainMenuFromSubMenu()
	{
		ShowMainMenu();
	}

	static void _PerformMainMenuOption(enMainMenuOptions option)
	{
		switch (option)
		{
			case ShowClientsList:
			{
				system("cls");
				_ShowClientListScreen();
				_GoBackToMainMenu();
				break;
			}
			case AddNewClient:
			{
				system("cls");
				_AddNewClientScreen();
				_GoBackToMainMenu();
				break;
			}
			case DeleteClient:
			{
				system("cls");
				_DeleteClientScreen();
				_GoBackToMainMenu();
				break;
			}
			case UpdateClientInfo:
			{
				system("cls");
				_UpdateClientInfoScreen();
				_GoBackToMainMenu();
				break;
			}
			case FindClient:
			{
				system("cls");
				_FindClientScreen();
				_GoBackToMainMenu();
				break;
			}
			case Transactions:
			{
				system("cls");
				_ShowTransactionsMenu();
				_GoBackToMainMenuFromSubMenu();
				break;
			}
			case ManageUsers:
			{
				system("cls");
				_ShowManageUsersMenu();
				_GoBackToMainMenuFromSubMenu();
			}
			case LoginRegister:
			{
				system("cls");
				_ShowLogInRegisterScreen();
				_GoBackToMainMenu();
			}
			case CurrencyExchange:
			{
				system("cls");
				_ShowCurrencyExchangeScreen();
				_GoBackToMainMenuFromSubMenu();
			}
			case Logout:
			{
				system("cls");
				_Logout();
				break;
			}
		}
	}


public:
	static void ShowMainMenu()
	{
		system("cls");
		_DrawScreenHeader("\tMain Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		
		_PerformMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
	}
};

