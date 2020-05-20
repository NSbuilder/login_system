#pragma once
#include <queue>
#include "Helper.h"
#include "Message.h"

enum class CallSettings
{
	BY_USERNAME = 1, BY_NICKNAME
};

enum class DataType
{
	USERNAME, PASSWORD, NICKNAME
};

class Account
{
public:
	Account(string_view input1, string_view input2);
	~Account();

	const string_view GetData(DataType ThisDataType) const;
	const bool FindAcc(string_view input1) const;
	const bool CheckLogin(string_view input2) const;
	const bool IsNicknameEmpty() const;
	const CallSettings GetCallSetting() const;

	void SetPassword(string_view input2);
	void SetNickname(string_view input1);
	void SetCallSetting(CallSettings temp);
	void InsertMessage(Message& msg);

	queue<Message>& GetMessages();

private:
	queue<Message> m_MessageBox;
	string m_username;
	string m_password;
	string m_nickname;
	CallSettings m_callSetting;
};