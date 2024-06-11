#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Global.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "../Libs/clsString.h"
#include "../Libs/clsDate.h"

using namespace std;

string const File = "ClientData.txt";
string const TransferLogFile = "TransferLog.txt";

class clsBankClient : public clsPerson
{

private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddMode = 2 };

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;
	struct stTransferLog;


	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vRecordData = clsString::Split(Line, Seperator);
		return clsBankClient
		(
			enMode::UpdateMode,
			vRecordData[0],
			vRecordData[1],
			vRecordData[2],
			vRecordData[3],
			vRecordData[4],
			vRecordData[5],
			stof(vRecordData[6])
		);
	}

	static string _ConvertClientObjecttoLine(clsBankClient Client, string Seperator = "#//#")
	{
		string Line = Client.AccountNumber() + Seperator;
		Line += Client.PinCode + Seperator;
		Line += Client.FirstName + Seperator;
		Line += Client.LastName + Seperator;
		Line += Client.Email + Seperator;
		Line += Client.Phone + Seperator;
		Line += to_string(Client.AccountBalance);
		return Line;
	}

	static vector<clsBankClient> _LoadClientDataFormFile()
	{
		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open(File, ios::in);

		string Line;

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				vClients.push_back(_ConvertLinetoClientObject(Line));
			}
			MyFile.close();
		}
		return vClients;
	}

	static void _SaveClientDataToFile(vector<clsBankClient> vClients)
	{
		fstream Myfile;
		Myfile.open(File, ios::out);

		string DataLine;

		if (Myfile.is_open())
		{
			for (clsBankClient C : vClients)
			{
				if (C._MarkForDelete == false)
				{
					DataLine = _ConvertClientObjecttoLine(C);
					Myfile << DataLine << endl;
				}
			}
			Myfile.close();
		}
	}

	static void _AddClientDataToFile(clsBankClient Client)
	{
		fstream Myfile;
		Myfile.open(File, ios::out | ios::app);

		string DataLine;

		if (Myfile.is_open())
		{
			DataLine = _ConvertClientObjecttoLine(Client);
			Myfile << DataLine << endl;
			Myfile.close();
		}
	}

	void _Update()
	{
		vector<clsBankClient> _vClients;

		_vClients = _LoadClientDataFormFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientDataToFile(_vClients);
	}

	void _Add()
	{
		_AddClientDataToFile(*this);
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _PrepareTransferLogRecord(clsBankClient SourceClient, clsBankClient DestinationClient, double Amount, clsUser CurrentUser, string Seperator = "#//#")
	{
		string Line = "";
		Line += clsDate::DateTimeToString(clsDate()) + Seperator;
		Line += SourceClient.AccountNumber() + Seperator;
		Line += DestinationClient.AccountNumber() + Seperator;
		Line += to_string(Amount) + Seperator;
		Line += to_string(SourceClient.AccountBalance) + Seperator;
		Line += to_string(DestinationClient.AccountBalance) + Seperator;
		Line += CurrentUser.UserName;

		return Line;
	}

	static stTransferLog _ConvertTransferLogRecordToData(string Line ,string Seperator = "#//#")
	{
		vector<string> vData = clsString::Split(Line, Seperator);
		stTransferLog TransferData;
		TransferData.DateTime = vData[0];
		TransferData.SourceClientAccountNumber = vData[1];
		TransferData.DistenationClientAccountNumber = vData[2];
		TransferData.TransferAmount = stod(vData[3]);
		TransferData.SourceClientBalance = stod(vData[4]);
		TransferData.DistenationClientBalance = stod(vData[5]);
		TransferData.UserName = vData[6];
		return TransferData;
	}

	static void _TransferLog(clsBankClient SClient, clsBankClient DClient, double Amount, clsUser CUser)
	{
		fstream MyFile;
		string DataLine = "";

		MyFile.open(TransferLogFile, ios::out | ios::app);

		if (MyFile.is_open())
		{
			DataLine = _PrepareTransferLogRecord(SClient, DClient, Amount, CUser);
			MyFile << DataLine << endl;
		}
		MyFile.close();
	}

public:
	clsBankClient(enMode Mode, string AccountNumber, string PinCode, string FirstName, string LastName, string Email, string Phone, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool isEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	static clsBankClient Find(string AccountNumber)
	{
		/*vector<clsBankClient> vCLients;*/

		fstream	MyFile;
		MyFile.open(File, ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
				/*vCLients.push_back(Client);*/
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		/*vector<clsBankClient> vCLients;*/

		fstream	MyFile;
		MyFile.open(File, ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
				/*vCLients.push_back(Client);*/
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.isEmpty());
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddMode, AccountNumber, "", "", "", "", "", 0);
	}

	enum enSaveResults { svFaildEmptyObject = 1, svSucceeded = 2, svFailedAccountNumberExists = 3 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsBankClient::EmptyMode:
		{
			return enSaveResults::svFaildEmptyObject;
		}
		case clsBankClient::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
		}
		case clsBankClient::AddMode:
		{
			//You Should Test All Cases In the Logic-Layer
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFailedAccountNumberExists;
			}
			else
			{
				_Add();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}
		}
	}

	bool Delete()
	{
		vector<clsBankClient> vClients = _LoadClientDataFormFile();

		for (clsBankClient& Client : vClients)
		{
			if (Client.AccountNumber() == _AccountNumber)
			{
				Client._MarkForDelete = true;
				break;
			}
		}
		_SaveClientDataToFile(vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientDataFormFile();
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient> vClients = clsBankClient::GetClientsList();

		double Totle = 0.0;

		for (clsBankClient& C : vClients)
		{
			Totle += C.AccountBalance;
		}

		return Totle;
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount < _AccountBalance)
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
		else
		{
			return false;
		}
	}

	static bool Transfer(clsBankClient& Client1, clsBankClient& Client2, double TransferAmount)
	{
		if (TransferAmount < Client1.AccountBalance)
		{
			Client1.AccountBalance -= TransferAmount;
			Client2.AccountBalance += TransferAmount;
			_TransferLog(Client1, Client2, TransferAmount, CurrentUser);
			return true;
		}
		else
		{
			return false;
		}
	}

	struct stTransferLog
	{
		string DateTime;
		string SourceClientAccountNumber;
		string DistenationClientAccountNumber;
		double TransferAmount;
		double SourceClientBalance;
		double DistenationClientBalance;
		string UserName;
	};
	
	static vector<stTransferLog> GetTransferLogList()
	{
		vector<stTransferLog> vTransferData;
		string DataLine;

		fstream MyFile;

		MyFile.open(TransferLogFile, ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, DataLine))
			{
				vTransferData.push_back(_ConvertTransferLogRecordToData(DataLine));
			}
			MyFile.close();
		}

		return vTransferData;
	}
};