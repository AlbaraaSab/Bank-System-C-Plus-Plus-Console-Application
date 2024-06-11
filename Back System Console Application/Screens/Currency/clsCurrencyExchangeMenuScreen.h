#pragma once
#include "../clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeMenuScreen : protected clsScreen
{
private:

	enum enCurrencyMenu { eCurrenciesList = 1, eFindCurrency = 2, eUpdateCurrencyRate = 3, eCurrencyCalculator = 4, eMainMenu = 5 };

	static short _ReadCurrencyMenuOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short option = clsInputValidate<short>::ReadNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return option;
	}

	static void _ShowCurrenciesListScreen()
	{
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateCurrencyRateScreen()
	{
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _GoBackToCurrencyExchangeMenu()
	{
		cout << setw(37) << left << "" << "\n\n\tPress any key to go back to Currency Exchange Menue...\n";
		system("pause>0");
		ShowCurrencyExChangeMenu();
	}

	static void _PerformCurrencyMenuOption(enCurrencyMenu option)
	{
		switch (option)
		{
			case eCurrenciesList:
			{
				system("cls");
				_ShowCurrenciesListScreen();
				_GoBackToCurrencyExchangeMenu();
				break;
			}
			case eFindCurrency:
			{
				system("cls");
				_ShowFindCurrencyScreen();
				_GoBackToCurrencyExchangeMenu();
				break;
			}
			case eUpdateCurrencyRate:
			{
				system("cls");
				_ShowUpdateCurrencyRateScreen();
				_GoBackToCurrencyExchangeMenu();
				break;
			}
			case eCurrencyCalculator:
			{
				system("cls");
				_ShowCurrencyCalculatorScreen();
				_GoBackToCurrencyExchangeMenu();
				break;
			}
			case eMainMenu:
			{
			}
		}
	}

public:

	static void ShowCurrencyExChangeMenu()
	{
		system("cls");
		_DrawScreenHeader("\tCurrency Exchange Menu Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tCurrency Exchange Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Currencies List.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Currency Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformCurrencyMenuOption((enCurrencyMenu)_ReadCurrencyMenuOption());
	}
};

