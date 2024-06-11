#pragma once
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Core/clsUser.h"
#include "../../Libs/clsInputValidate.h"

class clsTransferScreen :
    protected clsScreen
{

private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Info:";
		cout << "\n_________________________________\n\n";
		cout << "AccountNumber   :  " << Client.AccountNumber() << endl;
		cout << "FullName        :  " << Client.FullName() << endl;
		cout << "AccountBalance  :  " << Client.AccountBalance << endl;
		cout << "\n_________________________________\n\n";
	}

	static clsBankClient _FindClient(string message)
	{
		string AccountNumber = "";
		cout << message;
		AccountNumber = clsInputValidate<string>::ReadString();

		while (!(clsBankClient::IsClientExist(AccountNumber)))
		{
			cout << "\nThe Account Number is not Exist\nPlease try again...\n\n";
			AccountNumber = clsInputValidate<string>::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return Client;
	}

public:

    static void ShowTransferScreen()
    {

		_DrawScreenHeader("Transfer Screen");


		clsBankClient Client1 = _FindClient("Please Enter Account Number to Transfer From: ");
		_PrintClient(Client1);


		clsBankClient Client2 = _FindClient("Please Enter Account Number to Transfer To: ");
		_PrintClient(Client2);

		double TransferAmount = 0.0;

		cout << "\nEnter Transfer Amount: ";
		TransferAmount = clsInputValidate<double>::ReadNumber();

		while (TransferAmount > Client1.GetAccountBalance())
		{
			cout << "\nAmount Exceeds the Client1 Balance, you can withdraw up to : " << Client1.AccountBalance << endl;
			cout << "\nEnter Transfer Amount: ";
			TransferAmount = clsInputValidate<double>::ReadNumber();
		}


		char e = 'n';
		cout << "\nAre You Sure You Want To Perform This Transaction? [Y/N] ";
		cin >> e;
		if (toupper(e) == 'Y')
		{
			if (clsBankClient::Transfer(Client1, Client2, TransferAmount))
			{
				Client1.Save();
				Client2.Save();
				cout << "\nDone Successfully\n";
				
				_PrintClient(Client1);

				_PrintClient(Client2);
			}
			else
			{
				cout << "\nAmount Exceeds the Client1 Balance, you can withdraw up to : " << Client1.AccountBalance << endl;
			}
		}
		else
		{
			cout << "\nTransfer Cancelled.";
		}

    }

};

