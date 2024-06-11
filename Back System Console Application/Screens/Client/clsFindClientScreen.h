#pragma once
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Libs/clsInputValidate.h"

class clsFindClientScreen : protected clsScreen
{

private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Info:";
		cout << "\n_________________________________\n\n";
		cout << "AccountNumber   :  " << Client.AccountNumber() << endl;
		cout << "PinCode         :  " << Client.PinCode << endl;
		cout << "LastName        :  " << Client.FullName() << endl;
		cout << "Email           :  " << Client.Email << endl;
		cout << "Phone           :  " << Client.Phone << endl;
		cout << "AccountBalance  :  " << Client.AccountBalance << endl;
		cout << "\n_________________________________\n\n";
	}

public:

	static void ShowFindClientScreen()
	{
		_DrawScreenHeader("Find Client Screen");

		string AccountNumber = "";
		cout << "Enter an Account Number: ";
		AccountNumber = clsInputValidate<string>::ReadString();

		while (!(clsBankClient::IsClientExist(AccountNumber)))
		{
			cout << "\nThe Account Number is not Exist\nPlease try again...\n\n";
			AccountNumber = clsInputValidate<string>::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
	}

};

