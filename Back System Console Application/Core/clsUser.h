#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Global.h"
#include "clsPerson.h"
#include "../Libs/clsString.h"
#include "../Libs/clsDate.h"
#include "../Libs/clsUtil.h"

using namespace std;

const string UsersFile = "Users.txt";
const string LogFile = "RegistLogs.txt";

class clsUser : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddMode = 2 };

	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedforDelete = false;


	struct stLoginRegister;


	static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#")
	{
		vector<string> vUser = clsString::Split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vUser[0], vUser[1], vUser[2], vUser[3], vUser[4], clsUtil::DecryptText(vUser[5], 3), stoi(vUser[6]));

	}

	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
	{
		string Line = "";
		Line += User.FirstName + Seperator;
		Line += User.LastName + Seperator;
		Line += User.Email + Seperator;
		Line += User.Phone + Seperator;
		Line += User._UserName + Seperator;
		Line += clsUtil::EncryptText(User._Password, 3) + Seperator;
		Line += to_string(User._Permissions);
		return Line;
	}

	static vector<clsUser> _LoadUsersDataFromFile()
	{
		vector<clsUser> vUsers;

		fstream MyFile;
		MyFile.open(UsersFile, ios::in);

		string Line;

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				vUsers.push_back(_ConvertLineToUserObject(Line));
			}
			MyFile.close();
		}
		return vUsers;
	}

	static void _SaveUserDataToFile(vector<clsUser> vUsers)
	{
		fstream MyFile;
		string DataLine = "";

		MyFile.open(UsersFile, ios::out);

		if (MyFile.is_open())
		{
			for (clsUser User : vUsers)
			{
				if (User._MarkedforDelete == false)
				{
					DataLine = _ConvertUserObjectToLine(User);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	static void _AddUserDataToFile(clsUser User)
	{
		fstream MyFile;
		string DataLine = "";

		MyFile.open(UsersFile, ios::out | ios::app);

		if (MyFile.is_open())
		{
			DataLine = _ConvertUserObjectToLine(User);
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	string _PrepareLogInRecored(string Seperator = "#//#")
	{
		string Line = clsDate::DateTimeToString(clsDate()) + Seperator;
		Line += UserName + Seperator;
		Line += clsUtil::EncryptText(Password, 3) + Seperator;
		Line += to_string(Permissions);
		return Line;
	}

	static stLoginRegister _ConvertLineToLoginRegisterStruct(string Line, string Seperator = "#//#")
	{
		vector<string> vData = clsString::Split(Line, Seperator);
		stLoginRegister loginRegister;

		loginRegister.DateTime = vData[0];
		loginRegister.UserName = vData[1];
		loginRegister.Password = clsUtil::DecryptText(vData[2], 3);
		loginRegister.Permission = stoi(vData[3]);

		return loginRegister;
	}

	void _Update()
	{
		vector<clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.UserName == _UserName)
			{
				User = *this;
				break;
			}
		}
		_SaveUserDataToFile(vUsers);
	}

	void _Add()
	{
		return _AddUserDataToFile(*this);
	}


public:

	struct stLoginRegister
	{
		string UserName;
		string Password;
		string DateTime;
		int Permission;
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Pasword, int Permissions) 
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Pasword;
		_Permissions = Permissions;
	}


	void SetUserName(string Username)
	{
		_UserName = Username;
	}

	string GetUserName()
	{
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;


	bool IsMarkedForDelete()
	{
		return _MarkedforDelete;
	}

	bool IsEmptyUser()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static clsUser Find(string username)
	{
		vector<clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser User : vUsers)
		{
			if (User.UserName == username)
			{
				return User;
			}
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{
		vector<clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser User : vUsers)
		{
			if (User.UserName == UserName && User.Password == Password)
			{
				return User;
			}
		}
		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmptyUser());
	}

	static vector<clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	static clsUser GetAddNewUser(string UserName)
	{
		return clsUser(enMode::AddMode, "", "", "", "", UserName, "", 0);
	}

	enum SaveResults { svFailedEmpty = 0, svSucceeded = 1, svFailedUserNameExist = 2 };

	SaveResults Save()
	{
		switch (_Mode)
		{
			case clsUser::EmptyMode:
			{
				return svFailedEmpty;
			}
			case clsUser::UpdateMode:
			{
				_Update();
				return svSucceeded;
			}
			case clsUser::AddMode:
			{
				if (clsUser::IsUserExist(_UserName))
				{
					return svFailedUserNameExist;
				}
				else
				{
					_Add();
					_Mode = enMode::UpdateMode;
					return svSucceeded;
				}
			}
		}
	}

	bool Delete()
	{
		 vector<clsUser> vUsers = _LoadUsersDataFromFile();

		 for (clsUser& User : vUsers)
		 {
			 if (User.UserName == _UserName)
			 {
				 User._MarkedforDelete = true;
				 break;
			 }
		 }
		 clsUser::_SaveUserDataToFile(vUsers);

		 *this = _GetEmptyUserObject();
		 
		 return true;
	}

	enum ePermission
	{
		eAll = -1,
		pListClient = 1,
		pAddCLient = 2,
		pDeleteClient = 4,
		pUpdateClient = 8,
		pFindClient = 16,
		pTransactions = 32,
		pManageUsers = 64,
		pLoginRegister = 128
	};

	bool CheckAccessPermission(ePermission Permissions)
	{
		if (this->Permissions == ePermission::eAll)
			return true;

		if ((this->Permissions & Permissions) == Permissions)
			return true;
		else
			return false;
	}


	void RegisterLogIn()
	{
		fstream MyFile;
		string DataLine = _PrepareLogInRecored();

		MyFile.open(LogFile, ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;

			MyFile.close();
		}
	}

	static vector<stLoginRegister> GetLogInRegisterList()
	{
		vector<stLoginRegister> vLogRegister;
		string DataLine;

		fstream MyFile;

		MyFile.open(LogFile, ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, DataLine))
			{
				vLogRegister.push_back(_ConvertLineToLoginRegisterStruct(DataLine));
			}
			MyFile.close();
		}

		return vLogRegister;
	}


};

