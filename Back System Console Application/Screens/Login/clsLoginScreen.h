#pragma once
#include "../../Core/Global.h"
#include "../clsScreen.h"
#include "../../Core/clsUser.h"
#include "../../Libs/clsInputValidate.h"
#include "../clsMainScreen.h"

class clsLoginScreen : protected clsScreen
{
private:

	static bool _Login()
	{
		bool LoginFailed = false;
		short Counter = 3;

		string UserName, Password;

		do
		{

			if (LoginFailed)
			{
				cout << "\nInvalid Username/Password!\n";
				cout << "You Have " << Counter << " Trials to Login.\n\n";
			}

			if (Counter > 0)
			{
				cout << "Enter Username? ";
				UserName = clsInputValidate<string>::ReadString();

				cout << "Enter Password? ";
				Password = clsInputValidate<string>::ReadString();


				CurrentUser = clsUser::Find(UserName, Password);

				if (CurrentUser.IsEmptyUser())
				{
					LoginFailed = true;
					Counter--;
				}
				//OR YOU CAN WRITE THE CONDITION LIKE THIS:
				// LoginFailed = CurrentUser.IsEmptyUser();
			}
			else
			{
				cout << "\nYou Are Locked After 3 Failed Trials.\n";
				return false;
			}

		} while (LoginFailed);

		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenu();
		return true;
	}

public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("Login Screen");
		return _Login();
	}
};

