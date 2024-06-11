#pragma once
#include <iomanip>
#include "../clsScreen.h"
#include "../../Core/clsCurrency.h"


class clsCurrenciesListScreen : protected clsScreen
{
private:

	static void _PrintCurrencyRecord(clsCurrency Currency)
	{
		cout << setw(8) << left << "" << "| " << setw(28) << left << Currency.Country();
		cout << "| " << setw(15) << left << Currency.CurrencyCode();
		cout << "| " << setw(40) << left << Currency.CurrencyName();
		cout << "| " << setw(15) << left << Currency.Rate;
	}

public:

	static void ShowCurrenciesListScreen()
	{
		vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

		string title = "Currencies List Screen";
		string SubTitle = "\t\t( " + to_string(vCurrencies.size()) + ") Recorde(s)";

		_DrawScreenHeader(title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(28) << "Country";
        cout << "| " << left << setw(15) << "Currency Code";
        cout << "| " << left << setw(40) << "Currency Name";
        cout << "| " << left << setw(15) << "Rate";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vCurrencies.size() == 0)
            cout << "\t\t\t\tNo Transfer Logins Available In the System!";
        else

            for (clsCurrency Currency : vCurrencies)
            {

                _PrintCurrencyRecord(Currency);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

	}

};

