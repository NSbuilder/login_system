#include "AccountManager.h"

int main()
{
	PHandler System;
	unsigned short userChoice;
	
	while (true)
	{
		ClrScr();
		cout << string(43, '-') << "MADE BY Noam Sarusi (NSbuilder)" << string(43, '-') << endl << endl;
		cout << string(50, '=') << "MAIN MENU" << string(50, '=') << endl;
		cout << "1 - Create new account" << endl;
		cout << "2 - Login to an existing account" << endl;
		cout << "3 - About" << endl;
		cout << "4 - Destroy all data in the system and exit program" << endl;
		cout << string(50, '=') << "MAIN MENU" << string(50, '=') << endl;
		cout << "|> ";

		SInput(userChoice);

		switch (userChoice)
		{
			case 1:
				System.CreateAccount();
				break;
			case 2:
				System.Login();
				break;
			case 3:
				System.AboutProgram();
				break;
			case 4:
				return 0;
			default:
				ErrHandler(ErrType::INVALID_CHOICE);
				break;
		}
	}
}