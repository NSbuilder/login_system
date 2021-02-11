#include "AccountManager.h"

PHandler::PHandler()
{
	accExist = true;
	Gchat.reserve(51);
}

PHandler::~PHandler()
{
}


void PHandler::AboutProgram()
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

	if (IsThatUsernameTaken(input1))
	{
		ErrHandler(ErrType::TAKEN_USERNAME);
		return;
	}

	cout << "Choose a password: " << endl;
	cout << "|> ";
	cin >> input2;

	while (input2.length() < 8 || input2.length() > 32)
	{
		ErrHandler(ErrType::PASSWORD_LENGTH);

		ClrScr();
		cout << string(10, '=') << "CREATE NEW ACCOUNT" << string(10, '=') << endl;
		cout << "To cancle, type " << CANCLE << "." << endl;
		cout << "To continue, choose a valid password." << endl;
		cout << "|> ";
		cin >> input2;

		if (input2 == CANCLE)
		{
			cout << "the operation had been cancelled by the user." << endl;
			return;
		}
	}
	
	string input3;

	ClrScr();
	cout << "Do you want this account to be have admin privileges? (yes/no) " << endl;
	cin >> input3;

	if (input3 == "yes")
	{
		if (!Admin::HowManyAdmins())
		{
			AccList.push_front(make_unique<Admin>(input1, input2));
			ScrFriz();
			return;
		}
		else
		{
			cout << "There is already one admin. It is currently possible to create only 1 account with admin privileges." << endl;
		}
	}

	cout << "A new user account will be created." << endl;
	AccList.push_front(make_unique<Account>(input1, input2));
	ScrFriz();

}

void PHandler::Login()
{
	ClrScr();
	cout << string(10, '=') << "LOGIN TO YOUR ACCOUNT" << string(10, '=') << endl;
	cout << "Enter your username: " << endl;
	cout << "|> ";
	cin >> input1;

	cout << "Enter your password: " << endl;
	cout << "|> ";
	cin >> input2;

	prevIter = AccList.before_begin();

	for (iter = AccList.begin(); iter != AccList.end(); ++iter)
	{
		if ((*iter)->TryLogin(input1, input2))
		{
			AccMenu();
			return;
		}
		prevIter++;
	}

	ErrHandler(ErrType::ACCOUNT_NOT_FOUND);
	cout << "wrong details" << endl;
}

void PHandler::AccMenu()
{
	auto& tmptr = (*iter)->GetMessages();

	while (accExist)
	{
		ClrScr();
		cout << "Welcome, " << Welcome() << '!' << endl;

		if ((*iter)->IsAdmin())
		{
			cout << "@ADMIN" << endl;
		}

		cout << string(20, '=') << "MY ACCOUNT" << string(20, '=') << endl;
		cout << ACCOUNT_OPEN_MSGBOX << "- view your messages" << endl;
		cout << ACCOUNT_SEND_MSG << " - send a message for another user" << endl;
		cout << ACCOUNT_GCHAT << " - open global chat" << endl;
		cout << ACCOUNT_NICK << " - change your nickname settings" << endl;
		cout << ACCOUNT_CHANGE_PASS << " - change your account's password" << endl;
		cout << DISCONNECT << " - disconnect from your account" << endl;
		cout << ACCOUNT_DELETE_ACCOUNT << "- permanently delete your account" << endl;

		if ((*iter)->IsAdmin())
		{
			cout << ADMIN_MENU << " - Manage the system and user accounts ( Admins only )" << endl;
		}

		cout << string(20, '=') << "MY ACCOUNT" << string(20, '=') << endl;

		if (!tmptr.empty())
		{
			cout << string(20, ' ') << "*You have new messages*" << endl << endl;
		}

		cout << "|> ";
		cin >> input1;

		if (input1 == ACCOUNT_NICK)
		{
			NicknameConfig();
		}
		else if (input1 == ACCOUNT_CHANGE_PASS)
		{
			ChangePassword();
		}
		else if (input1 == DISCONNECT)
		{
			cout << "You have disconnected from your account." << endl;
			ScrFriz();
			return;
		}
		else if (input1 == ACCOUNT_DELETE_ACCOUNT)
		{
			DeleteAccount();
		}
		else if (input1 == ACCOUNT_SEND_MSG)
		{
			SendMsg();
		}
		else if (input1 == ACCOUNT_OPEN_MSGBOX)
		{
			OpenMsgBox(tmptr);
		}
		else if (input1 == ACCOUNT_GCHAT)
		{
			GlobalChat();
		}
		else if ((*iter)->IsAdmin())
		{
			if (input1 == ADMIN_MENU)
			{
				AdminMenu();
			}
		}
		else
		{
			ErrHandler(ErrType::INVALID_CHOICE);
		}

	}

	accExist = true;
	return;
}

bool PHandler::IsThatUsernameTaken(string_view username)
{
	for (iter = AccList.begin(); iter != AccList.end(); ++iter)
	{
		if ((*iter)->GetData(DataType::USERNAME) == username)
		{
			return true;
		}
	}

	return false;
}

const string_view PHandler::Welcome() const
{
	switch ((*iter)->GetCallSetting())
	{
		default: case NamePreferences::BY_USERNAME:
			return (*iter)->GetData(DataType::USERNAME);
		case NamePreferences::BY_NICKNAME:
			return (*iter)->GetData(DataType::NICKNAME);
	}
}


void PHandler::SendMsg()
{
	cout << "Which user do you want to send the message? Please write the username precisely" << endl;
	cout << "|> ";
	cin >> input1;

	for (auto& iter2 : AccList)
	{
		if (iter2->GetUsername(input1))
		{
			cout << "Enter messsage topic:" << endl;
			cout << "|> ";
			SInput(input1);
			cout << "Enter messsage:" << endl;
			cout << "|> ";
			SInput(input2, 0);

			if (!input1.empty() && !input2.empty())
			{
				string_view input3 { (*iter)->GetData(DataType::USERNAME) };
				Message tmp(input3, input2, input1);
				iter2->InsertMessage(tmp);
				return;
			}

		}
	}

	ErrHandler(ErrType::ACCOUNT_NOT_FOUND);
	cout << "The user you want to send the message to does not exist." << endl; //Add to errHandler
	ScrFriz();
}

void PHandler::OpenMsgBox(queue<Message>& tmptr)
{
	do
	{
		if (tmptr.empty())
		{
			cout << "No new messages :)" << endl;
			ScrFriz();
			return;
		}

		cout << "You will now review your messages from the oldest to the newest. Every message you see will get deleted immidiately afterwards." << endl << endl;

		cout << "-------------------------------------" << endl;
		cout << "Sender: " << tmptr.front().GetMsgSender() << endl << endl << endl;
		cout << "Topic: " << tmptr.front().GetMTopic() << endl << endl << endl;
		cout << "Message: " << tmptr.front().GetMsg() << endl << endl << endl;
		cout << "-------------------------------------" << endl;
		tmptr.pop();

		if (tmptr.empty())
		{
			cout << "No new messages :)" << endl;
			ScrFriz();
			return;
		}

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

void PHandler::GlobalChat()
{
	do
	{
		ClrScr();
		cout << "**********Global Chat**********" << endl;

		for (auto& tmpItr : Gchat)
		{
			cout << tmpItr.GetMsgSender() << ": " << tmpItr.GetMsg() << endl << endl;
		}

		cout << "**********Global Chat**********" << endl;


		if (Gchat.size() == 50)
		{
			Gchat.erase(Gchat.begin());
		}

		cout << endl << "To write a message type \"write\". To exit, type \"exit\"" << endl;
		cin >> input1;

		if (input1 == "write")
		{
			cout << "Enter message:" << endl;
			SInput(input1);
			Gchat.push_back(Message((*iter)->GetData(DataType::USERNAME), input1));
		}
		else if (input1 == "exit")
		{
			return;
		}
		else
		{
			ErrHandler(ErrType::INVALID_CHOICE);
			continue;
		}

		//ScrFriz();
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

	if (!(*iter)->ValidateLogin(input1))
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
		(*iter)->SetPassword(input2);
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

	if ((*iter)->IsNicknameEmpty())
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

void PHandler::NicknameControl()
{
	unsigned short temp;
	cout << "Hi, " << Welcome() << '!' << endl;
	cout << "Your nickname is already set." << endl;
	cout << "Do you want to call you by your name ( default ) or by your nickname?" << endl;
	cout << "1 - By Name ( Default )" << endl;
	cout << "2 - By Nickname" << endl;
	cout << "|> ";

	SInput(temp);

	if (temp == 1)
	{
		(*iter)->SetCallSetting(NamePreferences::BY_USERNAME);
	}
	else
	{
		(*iter)->SetCallSetting(NamePreferences::BY_NICKNAME);
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


void PHandler::AdminMenu()
{
	do
	{
		ClrScr();
		cout << string(20, '=') << "SYSTEM ADMINISTRATOR MENU" << string(20, '=') << endl;
		cout << "Welcome, @ADMIN " << Welcome() << '!' << endl;
		cout << ADMIN_GET_USERLIST << " - Get a list of all users in the system" << '!' << endl;
		cout << ADMIN_GET_USERDATA << " - Get login information to log into every account" << '!' << endl;
		cout << DISCONNECT << " - disconnect from menu" << endl;

		cout << string(20, '=') << "SYSTEM ADMINISTRATOR MENU" << string(20, '=') << endl;
		cin >> input1;

		if (input1 == ADMIN_GET_USERLIST)
		{
			AdminGetUserList();
		}
		else if (input1 == ADMIN_GET_USERDATA)
		{
			AdminGetUserData();
		}
		else if (input1 == DISCONNECT)
		{
			return;
		}
		else
		{
			ErrHandler(ErrType::INVALID_CHOICE);
		}
	} while (true);
}

void PHandler::AdminGetUserList()
{
	ClrScr();
	cout << "-------USERS-------" << endl;

	for (auto& v : AccList)
	{
		cout << v->GetData(DataType::USERNAME);

		if (v->GetData(DataType::USERNAME) == (*iter)->GetData(DataType::USERNAME))
		{
			cout << " (This account)";
		}

		cout << endl;
	}
	cout << "-------USERS-------" << endl;
	ScrFriz();
}

void PHandler::AdminGetUserData()
{
	ClrScr();
	cout << "This functionality is privacy invadious and insecure. It will be removed soon" << endl;
	ScrFriz();
}