#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../Libs/clsString.h"

using namespace std;

const string CurrencyFile = "Currencies.txt";

class clsCurrency
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1};

	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static string _ConvertCurrencyDataToRecord(clsCurrency Currency, string Seperator = "#//#")
	{
		string Line = "";
		Line += Currency.Country() + Seperator;
		Line += Currency.CurrencyCode() + Seperator;
		Line += Currency.CurrencyName() + Seperator;
		Line += to_string(Currency.Rate);
		return Line;
	}

	static clsCurrency _ConvertRecordToCurrencyData(string Line, string Seperator = "#//#")
	{
		vector<string> vData = clsString::Split(Line, Seperator);

		return clsCurrency(enMode::UpdateMode, vData[0], vData[1], vData[2], stof(vData[3]));

	}

	static vector<clsCurrency> _LoadCurrencyDataFromFile()
	{
		fstream MyFile;
		vector<clsCurrency> vCurrencies;
		string Line = "";

		MyFile.open(CurrencyFile, ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				vCurrencies.push_back(_ConvertRecordToCurrencyData(Line));
			}
			MyFile.close();
		}
		return vCurrencies;
	}

	static void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrencyData)
	{
		fstream MyFile;
		MyFile.open(CurrencyFile, ios::out);

		if (MyFile.is_open())
		{
			for (clsCurrency Currency : vCurrencyData)
			{
				string Line = _ConvertCurrencyDataToRecord(Currency);
				MyFile << Line << endl;
			}
			MyFile.close();
		}
	}

	static clsCurrency _GetEmptyCurrency()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	void _Update()
	{
		fstream MyFile;
		vector<clsCurrency> vCurrencies = _LoadCurrencyDataFromFile();

		for (clsCurrency& Currency : vCurrencies)
		{
			if (Currency.CurrencyCode() == CurrencyCode())
			{
				Currency = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(vCurrencies);
	}


public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void SetRate(float Rate)
	{
		_Rate = Rate;
	}

	float GetRate()
	{
		return _Rate;
	}
	__declspec(property(get = GetRate, put = SetRate)) float Rate;

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	static clsCurrency FindByCode(string code)
	{
		code = clsString::CovertStringToUpperCase(code);

		vector<clsCurrency> vCurrencies = _LoadCurrencyDataFromFile();

		for (clsCurrency Currency : vCurrencies)
		{
			if (Currency.CurrencyCode() == code)
			{
				return Currency;
			}
		}
		return _GetEmptyCurrency();
	}

	static clsCurrency FindByCountry(string country)
	{
		country = clsString::CovertStringToUpperCase(country);

		vector<clsCurrency> vCurrencies = _LoadCurrencyDataFromFile();

		for (clsCurrency Currency : vCurrencies)
		{
			if (clsString::CovertStringToUpperCase(Currency.Country()) == country)
			{
				return Currency;
			}
		}
		return _GetEmptyCurrency();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}

	static vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}

	void UpdateRate(float rate)
	{
		Rate = rate;
		_Update();
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate);
	}

	float ConvertToOtherCurrency(clsCurrency ToCurrency, float AmountInUSD)
	{
		/*float AmountInUSD = ConvertToUSD(Amount);*/

		if (ToCurrency.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * ToCurrency.Rate);
	}

};

