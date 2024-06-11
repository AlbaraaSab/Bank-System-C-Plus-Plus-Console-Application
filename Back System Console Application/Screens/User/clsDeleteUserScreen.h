#pragma once
#include "../clsScreen.h"
#include "../../Core/clsUser.h"
#include "../../Libs/clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
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

	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("Delete User Screen.");


		string UserName = "";
		cout << "\nEnter User UserName: ";
		UserName = clsInputValidate<string>::ReadString();

		while (!(clsUser::IsUserExist(UserName)))
		{
			cout << "\nUserName Is Not Found...\nTry Again: ";
			UserName = clsInputValidate<string>::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		cout << "\n\nDo You Want To Delete This User? [Y/N] ";
		char answer;
		cin >> answer;

		if (toupper(answer) == 'Y')
		{
			if (User.Delete())
			{
				cout << "\nUser Deleted Successfully\n";
				_PrintUser(User);
			}
			else
			{
				cout << "\nError User was not Deleted...\n";
			}
		}

	}
};

