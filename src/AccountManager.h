#pragma once
#include "Account.h"
#include "Helper.h"
#include "Admin.h"
#include <forward_list>
#include <memory>

class PHandler final
{
public:
	PHandler();
	~PHandler();

	void AboutProgram();

	void CreateAccount();
	bool IsThatUsernameTaken(string_view username);

	void Login();

	void AccMenu();
	const string_view Welcome() const;
	void SendMsg();
	void OpenMsgBox(queue<Message>& tmptr);
	void GlobalChat();
	void ChangePassword();
	void NicknameConfig();
	void NicknameControl();
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

	static constexpr string_view ACCOUNT_OPEN_MSGBOX {"/messbox"};
	static constexpr string_view ACCOUNT_SEND_MSG {"/msg"};
	static constexpr string_view ACCOUNT_CHANGE_PASS { "/changepass" };
	static constexpr string_view ACCOUNT_NICK { "/nickname" };
	static constexpr string_view ACCOUNT_GCHAT { "/gchat" };

	static constexpr string_view ACCOUNT_DELETE_ACCOUNT { "/DELETE_MY_ACCOUNT" };
	static constexpr string_view ADMIN_MENU { "/admenu" };

	static constexpr string_view ADMIN_GET_USERLIST { "/userlist" };
	static constexpr string_view ADMIN_GET_USERDATA { "/getudata" };

	static constexpr string_view CANCLE { "cancle" };
	static constexpr string_view CONFIRM { "CONFIRM" };
	static constexpr string_view DISCONNECT {"/disconnect"};
};