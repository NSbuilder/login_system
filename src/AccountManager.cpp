#include "AccountManager.h"

PHandler::PHandler()
{
	accExist = true;
}

PHandler::~PHandler()
{
}

void PHandler::About()
{
	ClrScr();
	cout << string(10, '-') << endl << endl << "This program was made by Noam Sarusi ( NSbuilder )" << endl << endl;
	cout << string(10, '-') << endl << endl << "To stay updated, head to: github.com/NSbuilder/login_system" << endl << endl;
	ScrFriz();
}

void PHandler::CreateAccount()
{
	ClrScr();
	cout << string(10, '=') << "CREATE NEW ACCOUNT" << string(10, '=') << endl;
	cout << "Choose your username: " << endl;
	cout << "|> ";
	cin >> input1;

	for (iter = AccList.begin(); iter != AccList.end(); ++iter)
	{
		if (iter->GetData(DataType::USERNAME) == input1)
		{
			ErrHandler(ErrType::TAKEN_USERNAME);
			return;
		}
	}

	cout << "Choose a password: " << endl;
	cout << "|> ";
	cin >> input2;

	while (input2.length() < 8 || input2.length() > 32)
	{
		ErrHandler(ErrType::PASSWORD_LENGTH);

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

	AccList.push_front(Account(input1, input2));
	ScrFriz();
}

void PHandler::Login()
{
	ClrScr();
	cout << string(10, '=') << "LOGIN TO YOUR ACCOUNT" << string(10, '=') << endl;
	cout << "Enter your username: " << endl;
	cout << "|> ";
	cin >> input1;
	prevIter = AccList.before_begin();

	for (iter = AccList.begin(); iter != AccList.end(); ++iter)
	{

		if (iter->FindAcc(input1))
		{
			cout << "Enter your password: " << endl;
			cout << "|> ";
			cin >> input2;

			if (iter->CheckLogin(input2))
			{
				AccMenu();
				return;
			}

			ErrHandler(ErrType::ACCOUNT_NOT_FOUND);
			return;
		}

		prevIter++;

	}

	cout << "Enter your password: " << endl;
	cout << "|> ";
	cin >> input2;

	ErrHandler(ErrType::ACCOUNT_NOT_FOUND);
}

void PHandler::AccMenu()
{
	auto& tmptr = iter->GetMessages();
	while (accExist)
	{
		ClrScr();
		cout << "Welcome, " << WelcomeUser() << '!' << endl;
		cout << string(20, '=') << "SYSTEM COMMANDS" << string(20, '=') << endl;
		cout << COMMAND_OPEN_MSGBOX << "- view your messages" << endl;
		cout << COMMAND_SEND_MSG << " - send a message for another user" << endl;
		cout << COMMAND_NICK << " - change your nickname settings" << endl;
		cout << COMMAND_CHANGE_PASS << " - change your account's password" << endl;
		cout << COMMAND_DISCONNECT << " - disconnect from your account" << endl;
		cout << COMMAND_DELETE_ACCOUNT << "- permanently delete your account" << endl;
		cout << string(20, '=') << "SYSTEM COMMANDS" << string(20, '=') << endl;

		if (!tmptr.empty())
		{
			cout << string(20, ' ') << "*You have new messages*" << endl << endl;
		}

		cout << "|> ";
		cin >> input1;

		if (input1 == COMMAND_NICK)
		{
			NicknameConfig();
		}
		else if (input1 == COMMAND_CHANGE_PASS)
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
		else if (input1 == COMMAND_SEND_MSG)
		{
			SendMsg();
		}
		else if (input1 == COMMAND_OPEN_MSGBOX)
		{
			OpenMsgBox(tmptr);
		}
		else
		{
			ErrHandler(ErrType::INVALID_CHOICE);
		}

	}

	accExist = true;
	return;
}

const string & PHandler::WelcomeUser() const
{
	switch (iter->GetCallSetting())
	{
		default: case CallSettings::BY_USERNAME:
			return iter->GetData(DataType::USERNAME);
		case CallSettings::BY_NICKNAME:
			return iter->GetData(DataType::NICKNAME);
	}
}

void PHandler::SendMsg()
{
	cout << "Which user do you want to send the message? Please write the username percisely" << endl;
	cout << "|> ";
	cin >> input1;

	for (auto iter2 = AccList.begin(); iter2 != AccList.end(); ++iter2)
	{
		if (iter2->FindAcc(input1))
		{
			cout << "Enter messsage topic:" << endl;
			cout << "|> ";

			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			getline(cin, input1);
			cout << "Enter messsage:" << endl;
			cout << "|> ";
			getline(cin, input2);

			if (!input1.empty() && !input2.empty())
			{
				string input3 = iter->GetData(DataType::USERNAME);
				Message tmp(input3, input1, input2);
				iter2->InsertMessage(tmp);
				return;
			}

		}
	}

	ErrHandler(ErrType::ACCOUNT_NOT_FOUND);
	cout << "The user you want to send the message to does not exist." << endl; //Add to errHandler
	ScrFriz();
}

void PHandler::OpenMsgBox(stack<Message>& tmptr)
{
	do
	{
		if (tmptr.empty())
		{
			cout << "No new messages :)" << endl;
			ScrFriz();
			return;
		}

		cout << "You will now review your messages from the newest to the oldest. Every message you see will get deleted immidiately afterwards." << endl << endl;

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
			ErrHandler(ErrType::INVALID_CHOICE);
			return;
		}
	} while (true);
}

void PHandler::ChangePassword()
{
	string input3;
	ClrScr();
	cout << string(10, '-') << "CHANGE PASSWORD" << string(10, '-') << endl;
	cout << "Enter your existing password: " << endl;
	cout << "|> ";
	cin >> input1;

	if (input1 != iter->GetData(DataType::PASSWORD))
	{
		ErrHandler(ErrType::WRONG_PASSWORD);
		return;
	}

	cout << "Enter a new password: " << endl;
	cout << "|> ";
	cin >> input2;

	while (input2.length() < 8 || input2.length() > 32)
	{
		ErrHandler(ErrType::PASSWORD_LENGTH);

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
		iter->SetPassword(input2);
		cout << "Your password had been updated." << endl;
		ScrFriz();
	}
	else
	{
		ErrHandler(ErrType::WRONG_PASSWORD);
		return;
	}
}

void PHandler::NicknameConfig()
{
	ClrScr();
	cout << string(10, '-') << "NICKNAME SETTINGS" << string(10, '-') << endl;

	if (iter->IsNicknameEmpty())
	{
		cout << "Choose your nickname: " << endl;
		cout << "|> ";
		cin >> input1;
		cout << "Are you SURE you want \"" << input1 << "\" to be your nickname? you can't change it later!" << endl;
		cout << "Type \"" << CONFIRM << "\" to set your nickname to \"" << input1 << "\" or any other string to cancel." << endl;
		cout << "|> ";
		cin >> input2;

		if (input2 == CONFIRM)
		{
			iter->SetNickname(input1);
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

void PHandler::NicknameControl()
{
	unsigned short temp;
	cout << "Hi, " << WelcomeUser() << '!' << endl;
	cout << "Your nickname is already set." << endl;
	cout << "Do you want to call you by your name ( default ) or by your nickname?" << endl;
	cout << "1 - By Name ( Default )" << endl;
	cout << "2 - By Nickname" << endl;
	cout << "|> ";

	IntPut(temp);

	if (temp == 1)
	{
		iter->SetCallSetting(CallSettings::BY_USERNAME);
	}
	else
	{
		iter->SetCallSetting(CallSettings::BY_NICKNAME);
	}

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
		AccList.erase_after(prevIter);
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