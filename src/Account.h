#pragma once
#include <vector>
#include "Helper.h"
#include "Message.h"

enum CallSettings
{
	BY_USERNAME = 1, BY_NICKNAME
};

enum DataType
{
	USERNAME, PASSWORD, NICKNAME
};

class Account
{
public:
	Account(string& input1, string& input2);
	~Account();

	const string& GetData(DataType ThisDataType);
	const bool FindAcc(string& input1 );
	const bool CheckLogin(string& input2);
	const bool IsNicknameEmpty() const;
	const CallSettings GetCallSetting() const;

	void SetPassword(string& input2);
	void SetNickname(string& input1);
	void SetCallSetting(uint16_t temp);

private:
	string m_username;
	string m_password;
	string m_nickname;
	CallSettings m_callSetting;
	vector<Message> MessageBox;
};