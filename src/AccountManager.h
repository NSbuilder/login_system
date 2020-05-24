#pragma once
#include "Account.h"
#include "Helper.h"
#include "Admin.h"
#include <forward_list>
#include <memory>

class PHandler
{
public:
	PHandler();
	~PHandler();

	void About();

	void CreateAccount();
	void Login();
	void AccMenu();
	const string_view Welcome() const;

	void NicknameConfig();
	void NicknameControl();

	void SendMsg();
	void OpenMsgBox(queue<Message>& tmptr);
	
	void GlobalChat();

	void ChangePassword();
	void DeleteAccount();

	void AdMenu();
	void AdGetUserList();
	void AdGetUserData();
	

private:
	bool accExist;
	forward_list<unique_ptr<Account>> AccList;
	forward_list<unique_ptr<Account>>::iterator iter;
	forward_list<unique_ptr<Account>>::iterator prevIter;
	
	vector<Message> Gchat;

	string input1;
	string input2;

	const string_view ACCOUNT_OPEN_MSGBOX {"/messbox"};
	const string_view ACCOUNT_SEND_MSG {"/msg"};
	const string_view ACCOUNT_CHANGE_PASS {"/changepass"};
	const string_view ACCOUNT_NICK {"/nickname"};
	const string_view ACCOUNT_GCHAT{"/gchat"};
	
	const string_view ACCOUNT_DELETE_ACCOUNT {"/DELETE_MY_ACCOUNT"};
	const string_view ADMIN_MENU {"/admenu"};

	const string_view ADMIN_GET_USERLIST {"/userlist"};
	const string_view ADMIN_GET_USERDATA {"/getudata"};

	const string_view CANCLE {"cancle"};
	const string_view CONFIRM {"CONFIRM"};
	const string_view DISCONNECT {"/disconnect"};
};