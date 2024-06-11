#pragma once
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Libs/clsInputValidate.h"

class clsAddNewClientScreen : protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate<string>::ReadString();

		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate<string>::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate<string>::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate<string>::ReadString();

		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate<string>::ReadString();

		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate<float>::ReadNumber();
	}

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Info:";
		cout << "\n_________________________________\n\n";
		cout << "AccountNumber   :  " << Client.AccountNumber()<< endl;
		cout << "PinCode         :  " << Client.PinCode << endl;
		cout << "LastName        :  " << Client.FullName() << endl;
		cout << "Email           :  " << Client.Email << endl;
		cout << "Phone           :  " << Client.Phone << endl;
		cout << "AccountBalance  :  " << Client.AccountBalance << endl;
		cout << "\n_________________________________\n\n";
	}

public:

	static void ShowAddNewClientScreen()
	{
		_DrawScreenHeader("Add New Client Screen");

		string AccountNumber = "";
		cout << "Please Enter Account Number: ";
		AccountNumber = clsInputValidate<string>::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Account Number Is Already used, Choose anothe one: ";
			AccountNumber = clsInputValidate<string>::ReadString();
		}

		clsBankClient Client = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(Client);

		clsBankClient::enSaveResults SaveResult;

		SaveResult = Client.Save();


		switch (SaveResult)
		{
			case clsBankClient::svFaildEmptyObject:
			{
				cout << "\nError: An Empty Object\n";
				break;
			}
			case clsBankClient::svSucceeded:
			{
				cout << "\nClient Added Successfully\n";
				_PrintClient(Client);
				break;
			}
			case clsBankClient::svFailedAccountNumberExists:
			{
				cout << "\nAccount Number Is Already Exist.\n";
				break;
			}
		}
	}


};

