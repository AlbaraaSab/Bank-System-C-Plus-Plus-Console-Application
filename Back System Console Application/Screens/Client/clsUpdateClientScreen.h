#pragma once
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Libs/clsInputValidate.h"


class clsUpdateClientScreen : protected clsScreen
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
		cout << "AccountNumber   :  " << Client.AccountNumber() << endl;
		cout << "PinCode         :  " << Client.PinCode << endl;
		cout << "LastName        :  " << Client.FullName() << endl;
		cout << "Email           :  " << Client.Email << endl;
		cout << "Phone           :  " << Client.Phone << endl;
		cout << "AccountBalance  :  " << Client.AccountBalance << endl;
		cout << "\n_________________________________\n\n";
	}

public:


	static void ShowUpdateClientScreen()
	{
		_DrawScreenHeader("Update Client Screen");

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

		cout << " \nStart Update:\n";

		_ReadClientInfo(Client);

		clsBankClient::enSaveResults saveResults;

		saveResults = Client.Save();

		switch (saveResults)
		{
		case clsBankClient::svFaildEmptyObject:
			cout << "\nUpdate Failed...\n NO Client Found.\n";
			break;
		case clsBankClient::svSucceeded:
			cout << "\nUpdate Succeeded.\n";
			break;
		}

	}


};

