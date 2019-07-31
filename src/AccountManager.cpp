#include "AccountManager.h"

AccountManager::AccountManager()
{
	accountExist = true;
}

AccountManager::~AccountManager()
{
	for (iter = accList.begin(); iter != accList.end(); ++iter)
	{
		delete *iter;
	}
}

void AccountManager::CreateAccount()
{
	Cclear();
	cout << string(10, '=') << "CREATE NEW ACCOUNT" << string(10, '=') << endl;
	cout << "Choose your username: " << endl;
	cout << "> ";
	cin >> input1;

	for (iter = accList.begin(); iter != accList.end();)
	{

		if ((*iter)->GetData(USERNAME) == input1)
		{
			ErrorHandler(TAKEN_USERNAME);
			return;
		}
		else
		{
			++iter;
		}

	}

	cout << "Choose a password: " << endl;
	cout << "> ";
	cin >> input2;

	while (input2.length() < 8 || input2.length() > 32)
	{
		ErrorHandler(PASSWORD_LENGTH);

		Cclear();
		cout << "To cancle the account creation, type " << CANCLE << "." << endl;
		cout << "To continue, choose a valid password." << endl;
		cout << "> ";
		cin >> input2;

		if (input2 == CANCLE)
		{
			cout << "the operation had been cancelled by the user." << endl;
			return;
		}

		continue;

	}

	Account* account = new Account(input1, input2);
	accList.push_back(account);
	Cpause();
}

void AccountManager::Logger()
{
	Cclear();
	cout << string(10, '=') << "LOGIN TO YOUR ACCOUNT" << string(10, '=') << endl;
	cout << "Enter your account's username: " << endl;
	cout << "> ";
	cin >> input1;
	cout << "Enter your account's password: " << endl;
	cout << "> ";
	cin >> input2;

	for (iter = accList.begin(); iter != accList.end();)
	{

		if ((*iter)->CheckLogin(input1, input2))
		{
			AccSystem();
			return;
		}
		else
		{
			++iter;
		}

	}

	ErrorHandler(ACCOUNT_NOT_FOUND);
}

void AccountManager::AccSystem()
{
	while (accountExist)
	{
		Cclear();
		cout << "Welcome, " << WelcomeUser() << '!' << endl;
		cout << string(20, '=') << "SYSTEM COMMANDS" << string(20, '=') << endl;
		cout << COMMAND_NICKNAME << " - change your nickname settings" << endl;
		cout << COMMAND_CHANGE_PASSWORD << " - change your account's password" << endl;
		cout << COMMAND_DISCONNECT << " - disconnect from your account" << endl;
		cout << COMMAND_DELETE_ACCOUNT << "- permanently delete your account" << endl;
		cout << string(20, '=') << "SYSTEM COMMANDS" << string(20, '=') << endl;
		cout << "> ";
		cin >> input1;

		if (input1 == COMMAND_NICKNAME)
		{
			NicknameConfig();
		}
		else if (input1 == COMMAND_CHANGE_PASSWORD)
		{
			ChangePassword();
		}
		else if (input1 == COMMAND_DISCONNECT)
		{
			cout << "You have disconnected from your account." << endl;
			Cpause();
			return;
		}
		else if (input1 == COMMAND_DELETE_ACCOUNT)
		{
			DeleteAccount();
		}
		else
		{
			ErrorHandler(INVALID_CHOICE);
		}

	}

	accountExist = true;
	return;
}

const string & AccountManager::WelcomeUser() const
{
	switch ((*iter)->GetCallSetting())
	{
		default: case BY_USERNAME:
			return (*iter)->GetData(USERNAME);
		case BY_NICKNAME:
			return (*iter)->GetData(NICKNAME);
	}
}

void AccountManager::ChangePassword()
{
	string input3;
	Cclear();
	cout << string(10, '-') << "CHANGE PASSWORD" << string(10, '-') << endl;
	cout << "Enter your existing password: " << endl;
	cout << "> ";
	cin >> input1;

	if (input1 != (*iter)->GetData(PASSWORD))
	{
		ErrorHandler(WRONG_PASSWORD);
		return;
	}

	cout << "Enter a new password: " << endl;
	cout << "> ";
	cin >> input2;

	while (input2.length() < 8 || input2.length() > 32)
	{
		ErrorHandler(PASSWORD_LENGTH);

		cout << "To leave the password unchanged, type " << CANCLE << "." << endl;
		cout << "To continue, choose a new valid password." << endl;
		cout << "> ";
		cin >> input2;

		if (input2 == CANCLE)
		{
			cout << "the operation had been cancelled by the user." << endl;
			return;
		}

		continue;

	}

	cout << "Confirm new password: " << endl;
	cout << "> ";
	cin >> input3;

	if (input3 == input2)
	{
		(*iter)->SetPassword(input2);
		cout << "Your password had been updated." << endl;
		Cpause();
	}
	else
	{
		ErrorHandler(106);
		return;
	}
}

void AccountManager::NicknameConfig()
{
	Cclear();
	cout << string(10, '-') << "NICKNAME SETTINGS" << string(10, '-') << endl;

	if ((*iter)->IsNicknameEmpty())
	{
		ChooseNickname();

		if (input2 == CONFIRM)
		{
			(*iter)->SetNickname(input1);
			NicknameControl();
		}
		else
		{
			cout << "Operation cancelled by user. no changes occurred." << endl;
			Cpause();
		}
	}
	else
	{
		NicknameControl();
	}
}

void AccountManager::ChooseNickname()
{
	cout << "Choose your nickname: " << endl;
	cout << "> ";
	cin >> input1;
	cout << "Are you SURE you want \"" << input1 << "\" to be your nickname? you can't change it later!" << endl;
	cout << "Type \"" << CONFIRM << "\" to set your nickname to \"" << input1 << "\" or any other string to cancel." << endl;
	cout << "> ";
	cin >> input2;
}

void AccountManager::NicknameControl()
{
	uint16_t temp;
	Cclear();
	cout << "Hi, " << WelcomeUser() << '!' << endl;
	cout << "Your nickname is already set." << endl;
	cout << "Do you want to call you by your name ( default ) or by your nickname?" << endl;
	cout << "1 - By Name ( Default )" << endl;
	cout << "2 - By Nickname" << endl;
	cout << "> ";

	CinToInt(temp);

	(*iter)->SetCallSetting(temp);
	Cpause();
}

void AccountManager::DeleteAccount()
{
	Cclear();
	cout << string(10, '-') << "DELETE ACCOUNT" << string(10, '-') << endl;
	cout << "Are you sure you want to delete your account + all the data stored in it? It can't be restored!!" << endl;
	cout << "Type \"" << CONFIRM << "\" to permanently delete your account or any other string to cancel." << endl;
	cout << "> ";
	cin >> input1;

	if (input1 == CONFIRM)
	{
		delete *iter;
		iter = accList.erase(iter);
		accountExist = false;
		cout << "Your Account had been deleted." << endl;
		Cpause();
	}
	else
	{
		cout << "Account deletion cancelled. no changes occurred." << endl;
		Cpause();
	}
}
