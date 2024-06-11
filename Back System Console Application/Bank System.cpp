#include <iostream>
#include "Screens/Login/clsLoginScreen.h"

using namespace std;

int main()
{
	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
		{
			break;
		}
	}

	return 0;
}