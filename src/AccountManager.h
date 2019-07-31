#pragma once
#include <list>
#include "Account.h"

class AccountManager
{
public:
	AccountManager();
	~AccountManager();
	void CreateAccount();
	void Logger();

	void AccSystem();
	const string& WelcomeUser() const;
	void ChangePassword();
	void NicknameConfig();
	void ChooseNickname();
	void NicknameControl();
	void DeleteAccount();
private:
	string input1;
	string input2;

	const string COMMAND_CHANGE_PASSWORD = "/changepass";
	const string COMMAND_NICKNAME = "/nickname";
	const string COMMAND_DISCONNECT = "/disconnect";
	const string COMMAND_DELETE_ACCOUNT = "/deleteacc";
	const string CANCLE = "CANCLE";
	const string CONFIRM = "CONFIRM";

	bool accountExist;
	list<Account*> accList;
	list<Account*>::iterator iter;
};