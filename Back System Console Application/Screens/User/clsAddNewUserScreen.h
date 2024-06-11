#pragma once
#include <iomanip>
#include "../clsScreen.h"
#include "../../Core/clsUser.h"
#include "../../Libs/clsInputValidate.h"

class clsAddNewUserScreen : clsScreen
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

	static int _ReadPermissionsToSet()
	{
		int Permission = 0;

		char Answer = 'Y';

		cout << "\nDo you want to give full access? [Y/N]  ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			return -1;
		}

		cout << "\nDo you want to give access to :/n";

		cout << "\nShow Client List? Y/N ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission += clsUser::ePermission::pListClient;
		}

		cout << "\nAdd New Client ? Y/N ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission += clsUser::ePermission::pAddCLient;
		}

		cout << "\nDelete Client? Y/N ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission += clsUser::ePermission::pDeleteClient;
		}

		cout << "\nUpdate Client? Y/N ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission += clsUser::ePermission::pUpdateClient;
		}

		cout << "\nFind Client? Y/N ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission += clsUser::ePermission::pFindClient;
		}

		cout << "\nTransactions? Y/N ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission += clsUser::ePermission::pTransactions;
		}

		cout << "\nManage Users? Y/N ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission += clsUser::ePermission::pManageUsers;
		}

		cout << "\nLogin Register? Y/N ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission += clsUser::ePermission::pLoginRegister;
		}

		return Permission;
	}

	static void _ReadNewUser(clsUser& User)
	{
		cout << "Enter FirstName? ";
		User.FirstName = clsInputValidate<string>::ReadString();

		cout << "Enter LastName? ";
		User.LastName = clsInputValidate<string>::ReadString();

		cout << "Enter Email? ";
		User.Email = clsInputValidate<string>::ReadString();

		cout << "Enter Phone? ";
		User.Phone = clsInputValidate<string>::ReadString();

		cout << "Enter Password? ";
		User.Password = clsInputValidate<string>::ReadString();

		User.Permissions = _ReadPermissionsToSet();
	}

public:

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("Add New User Screen");

		string UserName;

		cout << "\nEnter UserName: ";
		UserName = clsInputValidate<string>::ReadString();

		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nThis UserName Is In Use...\nChoose Another One: ";
			UserName = clsInputValidate<string>::ReadString();
		}

		clsUser User = clsUser::GetAddNewUser(UserName);

		_ReadNewUser(User);


		clsUser::SaveResults SaveResult;

		SaveResult = User.Save();

		switch (SaveResult)
		{
			case clsUser::svFailedEmpty:
			{
				cout << "\nError: An Empty Object\n";
				break;
			}
			case clsUser::svSucceeded:
			{
				cout << "\nUser Added Successfully\n";
				_PrintUser(User);
				break;
			}
			case clsUser::svFailedUserNameExist:
			{
				cout << "\nUserName Is Already Exist.\n";
				break;
			}
		}

	}

};

