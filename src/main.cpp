#include "AccountManager.h"

int main()
{
	PHandler* System = new PHandler;
	bool terminate = false;
    uint16_t choice;

	do
	{
		ClrScr();
		cout << string(43, '-') << "MADE BY Noam Sarusi ( NSbuilder )" << string(43, '-') << endl << endl;
		cout << string(50, '=') << "MAIN MENU" << string(50, '=') << endl;
		cout << "1 - Create new account" << endl;
		cout << "2 - Login to an existing account" << endl;
		cout << "3 - Exit" << endl;
		cout << string(50, '=') << "MAIN MENU" << string(50, '=') << endl;
		cout << "|> ";

		CinToInt(choice);

		switch (choice)
		{
			case 1:
				System->CreateAccount();
				break;
			case 2:
				System->Login();
				break;
			case 3:
				terminate = true;
				break;
			default:
				ErrHandler(INVALID_CHOICE);
				break;
		}

	} 
	while (!terminate);

	delete System;
	return 0;

}