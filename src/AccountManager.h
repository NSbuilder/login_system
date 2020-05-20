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
	const string_view WelcomeUser() const;

	void NicknameConfig();
	void NicknameControl();

	void SendMsg();
	void OpenMsgBox(queue<Message>& tmptr);
	
	//void GlobalChat();

	void ChangePassword();
	void DeleteAccount();


private:
	bool accExist;
	forward_list<Account> AccList;
	forward_list<Account>::iterator iter;
	forward_list<Account>::iterator prevIter;

	//queue<Message> Gchat;

	string input1;
	string input2;

	const string_view COMMAND_OPEN_MSGBOX { "/messbox" };
	const string_view COMMAND_SEND_MSG { "/msg" };
	const string_view COMMAND_CHANGE_PASS { "/changepass" };
	const string_view COMMAND_NICK { "/nickname" };
	const string_view COMMAND_DISCONNECT { "/disconnect" };
	const string_view COMMAND_DELETE_ACCOUNT { "/DELETE_MY_ACCOUNT" };
	const string_view CANCLE { "cancle" };
	const string_view CONFIRM { "CONFIRM" };
};