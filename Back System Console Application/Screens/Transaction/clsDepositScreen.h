#pragma once
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Libs/clsInputValidate.h"

class clsDepositScreen : protected clsScreen
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

	static void ShowDepositScreen()
	{
		_DrawScreenHeader("Deposit Screen");

		char e = 'n';
		string AccountNumber;

		cout << "\nEnter an Account Number: ";
		AccountNumber = clsInputValidate<string>::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nThe Account Number is not Exist\nPlease try again...\n\n";
			AccountNumber = clsInputValidate<string>::ReadString();
		}
		
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		double Amount = 0.0;
		cout << "\nPlease Enter Deposit amount? ";
		Amount = clsInputValidate<double>::ReadNumber();

		cout << "\nAre You Sure You Want To Perform This Transaction? [Y/N] ";
		cin >> e;
		if (toupper(e) == 'Y')
		{
			Client.Deposit(Amount);
			cout << "\nDone Successfully, New Balance is = " << Client.AccountBalance << endl;
		}
		else
		{
			cout << "\nTransaction Cancelled.\n";
		}
	}

};

