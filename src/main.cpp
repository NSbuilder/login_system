#include "AccountManager.h"

int main()
{
	AccountManager* Manager = new AccountManager;
	bool end = false;
    uint16_t choice;

	while (!end)
	{
		Cclear();
		cout << string(46, '-') << "MADE BY NSbuilder" << string(46, '-') << endl << endl;
		cout << string(50, '=') << "MAIN MENU" << string(50, '=') << endl;
		cout << "1 - Create new account" << endl;
		cout << "2 - Login to an existing account" << endl;
		cout << "3 - Exit" << endl;
		cout << string(50, '=') << "MAIN MENU" << string(50, '=') << endl;
		cout << "> ";

		CinToInt(choice);

		switch (choice)
		{
			case 1:
				Manager->CreateAccount();
				break;
			case 2:
				Manager->Logger();
				break;
			case 3:
				end = true;
				break;
			default:
				ErrorHandler(INVALID_CHOICE);
				break;
		}

	}

	delete Manager;
	return 0;

}