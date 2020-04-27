#pragma once
#include <list>
#include "Account.h"

class PHandler
{
public:
	PHandler();
	~PHandler();
	void CreateAccount();
	void Login();

	void AccSystem();
	const string& WelcomeUser() const;
	void SendMessage();
	void ChangePassword();
	void NicknameConfig();
	void ChooseNickname();
	void NicknameControl();
	void DeleteAccount();
private:
	string input1;
	string input2;

	const string COMMAND_SEND_MESSAGE = "/message";
	const string COMMAND_CHANGE_PASSWORD = "/changepass";
	const string COMMAND_NICKNAME = "/nickname";
	const string COMMAND_DISCONNECT = "/disconnect";
	const string COMMAND_DELETE_ACCOUNT = "/deleteacc";
	const string CANCLE = "CANCLE";
	const string CONFIRM = "CONFIRM";

	bool accountExist;
	list<Account*> AccList;
	list<Account*>::iterator iter;
};