#include "AccountManager.h"

PHandler::PHandler()
{
	accExist = true;
}

PHandler::~PHandler()
{
	for (iter = AccList.begin(); iter != AccList.end(); ++iter)
	{
		delete *iter;
	}
}

void PHandler::CreateAccount()
{
	ClrScr();
	cout << string(10, '=') << "CREATE NEW ACCOUNT" << string(10, '=') << endl;
	cout << "Choose your username: " << endl;
	cout << "|> ";
	cin >> input1;

	for (iter = AccList.begin(); iter != AccList.end();)
	{

		if ((*iter)->GetData(USERNAME) == input1)
		{
			ErrHandler(TAKEN_USERNAME);
			return;
		}
		else
		{
			++iter;
		}

	}

	cout << "Choose a password: " << endl;
	cout << "|> ";
	cin >> input2;

	while (input2.length() < 8 || input2.length() > 32)
	{
		ErrHandler(PASSWORD_LENGTH);

		ClrScr();
		cout << "To cancle the account creation, type " << CANCLE << "." << endl;
		cout << "To continue, choose a valid password." << endl;
		cout << "|> ";
		cin >> input2;

		if (input2 == CANCLE)
		{
			cout << "the operation had been cancelled by the user." << endl;
			return;
		}

		continue;

	}

	AccList.push_back(new Account(input1, input2));
	ScrFriz();
}

void PHandler::Login()
{
	ClrScr();
	cout << string(10, '=') << "LOGIN TO YOUR ACCOUNT" << string(10, '=') << endl;
	cout << "Enter your username: " << endl;
	cout << "|> ";
	cin >> input1;

	for (iter = AccList.begin(); iter != AccList.end();)
	{

		if ((*iter)->FindAcc(input1))
		{
			cout << "Enter your password: " << endl;
			cout << "|> ";
			cin >> input2;
			if ((*iter)->CheckLogin(input2))
			{
				AccMenu();
				return;
			}
			ErrHandler(ACCOUNT_NOT_FOUND);
			return;
		}
		else
		{
			++iter;
		}

	}

	cout << "Enter your password: " << endl;
	cout << "|> ";
	cin >> input2;

	ErrHandler(ACCOUNT_NOT_FOUND);
}

void PHandler::AccMenu()
{
	while (accExist)
	{
		ClrScr();
		cout << "Welcome, " << WelcomeUser() << '!' << endl;
		cout << string(20, '=') << "SYSTEM COMMANDS" << string(20, '=') << endl;
		cout << COMMAND_OPEN_MESSAGEBOX << "- view your messages" << endl;
		cout << COMMAND_SEND_MESSAGE << " - send a message for another user" << endl;
		cout << COMMAND_NICKNAME << " - change your nickname settings" << endl;
		cout << COMMAND_CHANGE_PASSWORD << " - change your account's password" << endl;
		cout << COMMAND_DISCONNECT << " - disconnect from your account" << endl;
		cout << COMMAND_DELETE_ACCOUNT << "- permanently delete your account" << endl;
		cout << string(20, '=') << "SYSTEM COMMANDS" << string(20, '=') << endl;
		cout << "|> ";
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
			ScrFriz();
			return;
		}
		else if (input1 == COMMAND_DELETE_ACCOUNT)
		{
			DeleteAccount();
		}
		else if (input1 == COMMAND_SEND_MESSAGE)
		{
			SendMsg();
		}
		else if (input1 == COMMAND_OPEN_MESSAGEBOX)
		{
			OpenMsgBox();
		}
		else
		{
			ErrHandler(INVALID_CHOICE);
		}

	}

	accExist = true;
	return;
}

const string & PHandler::WelcomeUser() const
{
	switch ((*iter)->GetCallSetting())
	{
		default: case BY_USERNAME:
			return (*iter)->GetData(USERNAME);
		case BY_NICKNAME:
			return (*iter)->GetData(NICKNAME);
	}
}

void PHandler::SendMsg()
{
	cout << "Which user do you want to send the message? Please write the username percisely" << endl;
	cout << "|> ";
	cin >> input1;

	for (auto iter2 = AccList.begin(); iter2 != AccList.end(); ++iter2)
	{
		if ((*iter2)->FindAcc(input1))
		{
			cout << "Enter messsage topic:" << endl;
			cout << "|> ";

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			getline(cin, input1);
			cout << "Enter messsage:" << endl;
			cout << "|> ";
			getline(cin, input2);

			if (!input1.empty() && !input2.empty())
			{
				string input3 = (*iter)->GetData(USERNAME);
				Message tmp(input3, input1, input2);
				(*iter2)->InsertMessage(tmp);
				return;
			}

		}
	}

	ErrHandler(ACCOUNT_NOT_FOUND);
	cout << "The user you want to send the message to does not exist." << endl; //Add to errHandler
	ScrFriz();
}

void PHandler::OpenMsgBox()
{
	auto& tmptr = (*iter)->GetMessages();

	if (tmptr.empty())
	{
		cout << "No new messages yet :)" << endl;
		ScrFriz();
		return;
	}
	else
	{

		cout << "You will now review your messages from the newest to the oldest. Every message you see will get deleted immidiately afterwards." << endl << endl;

		while (tmptr.size())
		{
			cout << "-------------------------------------" << endl;
			cout << "Sender: " << tmptr.top().GetMSender() << endl << endl << endl;
			cout << "Topic: " << tmptr.top().GetMTopic() << endl << endl << endl;
			cout << "Message: " << tmptr.top().GetM() << endl << endl << endl;
			cout << "-------------------------------------" << endl;
			tmptr.pop();

			cout << "Do you want to continue reviewing your messages? (yes/no)" << endl;
			cin >> input1;

			if (input1 == "no")
			{
				ScrFriz();
				return;
			}
			else if (input1 != "no" && input1 != "yes")
			{
				ErrHandler(INVALID_CHOICE);
				return;
			}


		}

		



	}
}

void PHandler::ChangePassword()
{
	string input3;
	ClrScr();
	cout << string(10, '-') << "CHANGE PASSWORD" << string(10, '-') << endl;
	cout << "Enter your existing password: " << endl;
	cout << "|> ";
	cin >> input1;

	if (input1 != (*iter)->GetData(PASSWORD))
	{
		ErrHandler(WRONG_PASSWORD);
		return;
	}

	cout << "Enter a new password: " << endl;
	cout << "|> ";
	cin >> input2;

	while (input2.length() < 8 || input2.length() > 32)
	{
		ErrHandler(PASSWORD_LENGTH);

		cout << "To leave the password unchanged, type " << CANCLE << "." << endl;
		cout << "To continue, choose a new valid password." << endl;
		cout << "|> ";
		cin >> input2;

		if (input2 == CANCLE)
		{
			cout << "the operation had been cancelled by the user." << endl;
			return;
		}

		continue;

	}

	cout << "Confirm new password: " << endl;
	cout << "|> ";
	cin >> input3;

	if (input3 == input2)
	{
		(*iter)->SetPassword(input2);
		cout << "Your password had been updated." << endl;
		ScrFriz();
	}
	else
	{
		ErrHandler(106);
		return;
	}
}

void PHandler::NicknameConfig()
{
	ClrScr();
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
			ScrFriz();
		}
	}
	else
	{
		NicknameControl();
	}
}

void PHandler::ChooseNickname()
{
	cout << "Choose your nickname: " << endl;
	cout << "|> ";
	cin >> input1;
	cout << "Are you SURE you want \"" << input1 << "\" to be your nickname? you can't change it later!" << endl;
	cout << "Type \"" << CONFIRM << "\" to set your nickname to \"" << input1 << "\" or any other string to cancel." << endl;
	cout << "|> ";
	cin >> input2;
}

void PHandler::NicknameControl()
{
	uint16_t temp;
	//ClrScr();
	cout << "Hi, " << WelcomeUser() << '!' << endl;
	cout << "Your nickname is already set." << endl;
	cout << "Do you want to call you by your name ( default ) or by your nickname?" << endl;
	cout << "1 - By Name ( Default )" << endl;
	cout << "2 - By Nickname" << endl;
	cout << "|> ";

	IntPut(temp);

	(*iter)->SetCallSetting(temp);
	ScrFriz();
}

void PHandler::DeleteAccount()
{
	ClrScr();
	cout << string(10, '-') << "DELETE ACCOUNT" << string(10, '-') << endl;
	cout << "Are you sure you want to delete your account + all the data stored in it? It can't be restored!!" << endl;
	cout << "Type \"" << CONFIRM << "\" to permanently delete your account or any other string to cancel." << endl;
	cout << "|> ";
	cin >> input1;

	if (input1 == CONFIRM)
	{
		delete *iter;
		iter = AccList.erase(iter);
		accExist = false;
		cout << "Your Account had been deleted." << endl;
		ScrFriz();
	}
	else
	{
		cout << "Account deletion cancelled. no changes occurred." << endl;
		ScrFriz();
	}
}
