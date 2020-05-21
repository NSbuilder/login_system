#include "Helper.h"

void ClrScr()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");

#endif
}

void ScrFriz()
{
#ifdef _WIN32
	system("pause");
#else
	cout << "Press enter to continue" << endl;
	cin.get();
#endif
}

void IntPut(unsigned short& choice)
{
	if (!(cin >> choice))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

void InputWithSpaces(string& input)
{
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, input);
}

void ErrHandler(ErrType errSort)
{
	ClrScr();
	cerr << "##########ERROR##########" << endl;

	switch (errSort)
	{
		case ErrType::INVALID_CHOICE:
			cerr << "You made an invalid choice!" << endl;
			break;
		case ErrType::USERNAME_LENGTH:
			cerr << "Your username must be at least 5 characters long and no longer than 20!" << endl;
			break;
		case ErrType::TAKEN_USERNAME:
			cerr << "This username is already taken!" << endl;
			break;
		case ErrType::PASSWORD_LENGTH:
			cerr << "Your password must be at least 8 characters long and no longer than 32!" << endl;
			break;
		case ErrType::ACCOUNT_NOT_FOUND:
			cerr << "Incorrect username or password." << endl;
			break;
		case ErrType::WRONG_PASSWORD:
			cerr << "Wrong password!" << endl;
			break;
		case ErrType::UNSAVED_NEW_PASSWORD:
			cerr << "Can't save new password because new password and conform password does not match!" << endl;
			break;
		default:
			break;
	}

	cout << "##########ERROR##########" << endl;
	ScrFriz();
}