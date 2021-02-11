#pragma once
#include "Message.h"
#include <queue>
#include <functional>

enum class NamePreferences
{
	BY_USERNAME = 1, BY_NICKNAME
};

enum class DataType
{
	USERNAME, NICKNAME
};

class Account
{
public:
	Account(string_view input1, string& input2);
	~Account();

	bool TryLogin(string_view input1, string& input2);
	const string_view GetData(DataType ThisDataType) const;
	const bool GetUsername(string_view input1) const;

	const bool ValidateLogin(string& input2);

	const bool IsNicknameEmpty() const;
	const NamePreferences GetCallSetting() const;
	const bool IsAdmin() const;

	void SetPassword(string_view input2);
	void SetNickname(string_view input1);
	void SetCallSetting(NamePreferences temp);
	void InsertMessage(Message& msg);

	const static unsigned HowManyAccounts();

	queue<Message>& GetMessages();

protected:
	queue<Message> m_MessageBox;
	string m_username;
	string m_nickname;
	size_t hashedPassword;

	NamePreferences m_callSetting;

	static unsigned accCounter;

	bool isAdmin = false;
};