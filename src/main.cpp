#include "AccountManager.h"

int main()
{
	bool terminate = false;
	unsigned short choice;
	PHandler System;
	
	do
	{
		ClrScr();
		cout << string(43, '-') << "MADE BY Noam Sarusi ( NSbuilder )" << string(43, '-') << endl << endl;
		cout << string(50, '=') << "MAIN MENU" << string(50, '=') << endl;
		cout << "1 - Create new account" << endl;
		cout << "2 - Login to an existing account" << endl;
		cout << "3 - About" << endl;
		cout << "4 - Exit" << endl;
		cout << string(50, '=') << "MAIN MENU" << string(50, '=') << endl;
		cout << "|> ";
		IntPut(choice);

		switch (choice)
		{
			case 1:
				System.CreateAccount();
				break;
			case 2:
				System.Login();
				break;
			case 3:
				System.About();
				break;
			case 4:
				terminate = true;
				break;
			default:
				ErrHandler(ErrType::INVALID_CHOICE);
				break;
		}

	} 
	while (!terminate);

	return 0;
}