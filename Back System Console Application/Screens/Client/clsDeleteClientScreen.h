#pragma once
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Libs/clsInputValidate.h"

class clsDeleteClientScreen : protected clsScreen
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
	static void ShowDeleteClientScreen()
	{

		_DrawScreenHeader("Delete Client Screen");

		string AccountNumber = "";
		cout << "\nEnter Client Account Number: ";
		AccountNumber = clsInputValidate<string>::ReadString();

		while (!(clsBankClient::IsClientExist(AccountNumber)))
		{
			cout << "\nAccount Number Is Not Found...\nTry Again: ";
			AccountNumber = clsInputValidate<string>::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		cout << "\n\nDo You Want To Delete This Client? [Y/N] ";
		char answer;
		cin >> answer;

		if (toupper(answer) == 'Y')
		{
			if (Client.Delete())
			{
				cout << "\nClient Deleted Successfully\n";
				_PrintClient(Client);
			}
			else
			{
				cout << "\nError Client was not Deleted...\n";
			}
		}
	}

};

