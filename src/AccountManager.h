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
	void AccMenu();
	const string& WelcomeUser() const;
	void DeleteAccount();

	void SendMsg();
	void OpenMsgBox();

	void ChangePassword();

	void NicknameConfig();
	void ChooseNickname();
	void NicknameControl();

private:
	bool accExist;
	list<Account*> AccList;
	list<Account*>::iterator iter;

	string input1;
	string input2;

	const string COMMAND_OPEN_MESSAGEBOX = "/messbox";
	const string COMMAND_SEND_MESSAGE = "/message";
	const string COMMAND_CHANGE_PASSWORD = "/changepass";
	const string COMMAND_NICKNAME = "/nickname";
	const string COMMAND_DISCONNECT = "/disconnect";
	const string COMMAND_DELETE_ACCOUNT = "/deleteacc";
	const string CANCLE = "CANCLE";
	const string CONFIRM = "CONFIRM";
};