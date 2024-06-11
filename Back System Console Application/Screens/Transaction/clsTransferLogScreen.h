#pragma once
#include <iomanip>
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"


class clsTransferLogScreen :
    protected clsScreen
{

private:

    static void _PrintTransferLoginRecordLine(clsBankClient::stTransferLog TransferData)
    {

        cout << setw(8) << left << "" << "| " << setw(25) << left << TransferData.DateTime;
        cout << "| " << setw(10) << left << TransferData.SourceClientAccountNumber;
        cout << "| " << setw(10) << left << TransferData.DistenationClientAccountNumber;
        cout << "| " << setw(10) << left << TransferData.TransferAmount;
        cout << "| " << setw(10) << left << TransferData.SourceClientBalance;
        cout << "| " << setw(10) << left << TransferData.DistenationClientBalance;
        cout << "| " << setw(10) << left << TransferData.UserName;
    }

public:

    static void ShowTransferLogScreen()
    {
        vector<clsBankClient::stTransferLog> vTransferData = clsBankClient::GetTransferLogList();

        string title = "Transfer Log Screen";
        string SubTitle = "\t\t( " + to_string(vTransferData.size()) + ") Recorde(s)";

        _DrawScreenHeader(title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(10) << "S.Account";
        cout << "| " << left << setw(10) << "D.Account";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "S.Balance";
        cout << "| " << left << setw(10) << "D.Balance";
        cout << "| " << left << setw(10) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferData.size() == 0)
            cout << "\t\t\t\tNo Transfer Logins Available In the System!";
        else

            for (clsBankClient::stTransferLog Record : vTransferData)
            {

                _PrintTransferLoginRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};

