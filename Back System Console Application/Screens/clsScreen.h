#pragma once
#include <iostream>
#include "../Libs/clsDate.h"
using namespace std;

class clsScreen
{
protected:
	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";

        cout << "\n\t\t\t\t\tUserName: " << CurrentUser.UserName;
        cout << "\n\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << endl << endl;
	}

    static void _ShowAccessDeniedMessage()
    {
        cout << "\n------------------------------------\n";
        cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin.";
        cout << "\n------------------------------------\n";
    }

};

