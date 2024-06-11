#pragma once
#include <iomanip>
#include "../clsScreen.h"
#include "../../Libs/clsInputValidate.h"
#include "../../Core/clsUser.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : clsScreen
{
private:
	enum enManageUserOptions
	{
		enShowUsersList = 1,
		enAddNewUser = 2,
		enDeleteUser = 3,
		enUpdateUser = 4,
		enFindUser = 5,
		MainMenu = 6,
	};

	static void _ShowUsersListScreen()
	{
		clsUsersListScreen::ShowClientsListScreen();
	}

	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _GoToManageUsersMenuScreen()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Manage Users Menu...\n";
		system("pause>0");
		ShowManageUsersMenu();
	}

	static short ReadManageUsersMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short option = clsInputValidate<short>::ReadNumberBetween(1, 6, "Enter Number between 1 to 6? ");
		return option;
	}

	static void _PerformManageUsersMenueOption(enManageUserOptions option)
	{
		switch (option)
		{
			case clsManageUsersScreen::enShowUsersList:
			{
				system("cls");
				_ShowUsersListScreen();
				_GoToManageUsersMenuScreen();
				break;
			}
			case clsManageUsersScreen::enAddNewUser:
			{
				system("cls");
				_ShowAddNewUserScreen();
				_GoToManageUsersMenuScreen();
				break;
			}
			case clsManageUsersScreen::enDeleteUser:
			{
				system("cls");
				_ShowDeleteUserScreen();
				_GoToManageUsersMenuScreen();
				break;
			}
			case clsManageUsersScreen::enUpdateUser:
			{
				system("cls");
				_ShowUpdateUserScreen();
				_GoToManageUsersMenuScreen();
				break;
			}
			case clsManageUsersScreen::enFindUser:
			{
				system("cls");
				_ShowFindUserScreen();
				_GoToManageUsersMenuScreen();
				break;
			}
			case clsManageUsersScreen::MainMenu:
			{
			}
		}
	}

public:
	static void ShowManageUsersMenu()
	{
		system("cls");
		_DrawScreenHeader("Manage Users Screen.");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t   Manage Users Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Users List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformManageUsersMenueOption((enManageUserOptions)ReadManageUsersMenueOption());
	}
};

