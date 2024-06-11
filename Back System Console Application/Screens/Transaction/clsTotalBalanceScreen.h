#pragma once
#include <iomanip>
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Libs/clsUtil.h"


class clsTotalBalanceScreen : protected clsScreen
{
private:
	static void _PrintClientBalanceRecord(clsBankClient Client)
	{
		cout << setw(25) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(40) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.AccountBalance;
	}

public:
	static void ShowTotalBalances()
	{
		vector<clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "Balances List Screen";
		string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

		_DrawScreenHeader(Title, SubTitle);


		cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
		cout << "__________________________\n" << endl;

		cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << setw(25) << left << "" << "\t\t_______________________________________________________";
		cout << "__________________________\n" << endl;

		double totalBalance = clsBankClient::GetTotalBalances();

		if (vClients.size() == 0)
		{
			cout << "\t\t\t\tNo Clients Available In The System!";
		}
		else
		{
			for (clsBankClient client : vClients)
			{
				_PrintClientBalanceRecord(client);
				cout << endl;
			}
		}
		cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
		cout << "__________________________\n" << endl;

		cout << setw(8) << left << "" << "\t\t\t\t\t\t\t     Total Balances = " << totalBalance << endl;
		cout << setw(8) << left << "" << "\t\t\t\t  ( " << clsUtil::NumberToText(totalBalance) << ")";

	}
};

