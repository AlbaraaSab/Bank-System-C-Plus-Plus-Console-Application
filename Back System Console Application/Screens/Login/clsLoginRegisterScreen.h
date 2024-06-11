#pragma once
#include <iomanip>
#include "../clsScreen.h"
#include "../../Core/clsUser.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void _PrintLogInRegisterRecordLine(clsUser::stLoginRegister LoginRegisterRecord)
	{

		cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.DateTime;
		cout << "| " << setw(20) << left << LoginRegisterRecord.UserName;
		cout << "| " << setw(20) << left << LoginRegisterRecord.Password;
		cout << "| " << setw(10) << left << LoginRegisterRecord.Permission;

	}


public:

	static void ShowLogInRegisterScreen()
	{
		vector<clsUser::stLoginRegister> vLoginRegister = clsUser::GetLogInRegisterList();


		string Title = "Login Register List Screen";
		string SubTitle = "\t   (" + to_string(vLoginRegister.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);


		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;


		if (vLoginRegister.size() == 0)
			cout << "\t\t\t\tNo Users Available In the System!";
		else

			for (clsUser::stLoginRegister LR : vLoginRegister)
			{

				_PrintLogInRegisterRecordLine(LR);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;


	}

};

