#pragma once
#include <forward_list>
#include "Account.h"

class PHandler
{
public:
	PHandler();
	~PHandler();

	void About();

	void CreateAccount();
	void Login();
	void AccMenu();
	const string& WelcomeUser() const;

	void NicknameConfig();
	void NicknameControl();

	void SendMsg();
	void OpenMsgBox(stack<Message>& tmptr);

	void ChangePassword();
	void DeleteAccount();
	

private:
	bool accExist;
	forward_list<Account> AccList;
	forward_list<Account>::iterator iter;
	forward_list<Account>::iterator prevIter;

	string input1;
	string input2;                                   
	
	const string COMMAND_OPEN_MSGBOX = "/messbox";
	const string COMMAND_SEND_MSG = "/msg";
	const string COMMAND_CHANGE_PASS = "/changepass";
	const string COMMAND_NICK = "/nickname";
	const string COMMAND_DISCONNECT = "/disconnect";
	const string COMMAND_DELETE_ACCOUNT = "/DELETE_MY_ACCOUNT";
	const string CANCLE = "cancle";
	const string CONFIRM = "CONFIRM";
};