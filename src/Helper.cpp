#include "Helper.h"

void CinToInt(uint16_t& choice)
{
	if (!(cin >> choice))
	{
		choice = 0;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

void ErrorHandler(uint16_t errNumber)
{
	Cclear();
	cout << "##########ERROR##########" << endl;

	switch (errNumber)
	{
		case INVALID_CHOICE:
			cout << "You made an invalid choice!" << endl;
			break;
		case USERNAME_LENGTH:
			cout << "Your username must be at least 5 characters long and no longer than 20!" << endl;
			break;
		case TAKEN_USERNAME:
			cout << "This username is already taken!" << endl;
			break;
		case PASSWORD_LENGTH:
			cout << "Your password must be at least 8 characters long and no longer than 32!" << endl;
			break;
		case ACCOUNT_NOT_FOUND:
			cout << "Account was not found! incorrect username or password." << endl;
			break;
		case WRONG_PASSWORD:
			cout << "Wrong password!" << endl;
			break;
		case UNSAVED_NEW_PASSWORD:
			cout << "Can't save new password because new password and conform password does not match!" << endl;
			break;
		default:
			cout << "UNKNOW ERROR!!!" << endl;
			break;
	}

	cout << "##########ERROR##########" << endl;
	Cpause();
}
