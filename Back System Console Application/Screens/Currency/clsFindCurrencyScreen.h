#pragma once
#include <iomanip>
#include "../clsScreen.h"
#include "../../Core/clsCurrency.h"
#include "../../Libs/clsInputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
{

private:

    enum enFindMode { enByCurrencyCode = 1, enByCountry = 2 };

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate;

        cout << "\n_____________________________\n";
    }

    static void _FindByCurrencyCode()
    {
        string Code;
        cout << "\nEnter Currency Code: ";
        Code = clsInputValidate<string>::ReadString();

        clsCurrency Currency = clsCurrency::FindByCode(Code);

        _PrintCurrency(Currency);
    }

    static void _FindByCountry()
    {
        string Country;
        cout << "\nEnter Currency Country: ";
        Country = clsInputValidate<string>::ReadString();

        clsCurrency Currency = clsCurrency::FindByCountry(Country);

        _PrintCurrency(Currency);
    }

    static short _ReadFindModeOption()
    {
        cout << setw(1) << left << "" << "Choose Find Mode? \n1: By Currency Code \n2: By Country\n";
        short option = clsInputValidate<short>::ReadNumberBetween(1, 2, "Enter Number between 1 to 2? ");
        return option;
    }

    static void _PerformFindModeOption(enFindMode option)
    {
        switch (option)
        {
            case enByCurrencyCode:
            {
                _FindByCurrencyCode();
                break;
            }
            case enByCountry:
            {
                _FindByCountry();
                break;
            }
        }
    }

public:

    static void ShowFindCurrencyScreen()
    {
        _DrawScreenHeader("\tFind Currency Screen");
        _PerformFindModeOption((enFindMode)_ReadFindModeOption());
    }

};

