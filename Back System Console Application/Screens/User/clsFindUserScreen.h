#pragma once
#include "../clsScreen.h"
#include "../../Core/clsUser.h"
#include "../../Libs/clsInputValidate.h"

class clsFindUserScreen : protected clsScreen
{

private:
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Info:";
		cout << "\n_________________________________\n\n";
		cout << "UserName		 :  " << User.UserName << endl;
		cout << "FullName        :  " << User.FullName() << endl;
		cout << "Email           :  " << User.Email << endl;
		cout << "Phone           :  " << User.Phone << endl;
		cout << "Password        :  " << User.Password << endl;
		cout << "Permissions	 :  " << User.Permissions << endl;
		cout << "\n_________________________________\n\n";
	}


public:
	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("Find User Screen.");

		string UserName = "";
		cout << "Enter an UserName: ";
		UserName = clsInputValidate<string>::ReadString();

		while (!(clsUser::IsUserExist(UserName)))
		{
			cout << "\nThe UserName is not Exist\nPlease try again...\n\n";
			UserName = clsInputValidate<string>::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);
	}
};

