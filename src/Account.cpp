#include "Account.h"

Account::Account(string& input1, string& input2)
{
	m_username = input1;
	m_password = input2;
	m_callSetting = BY_USERNAME;
}

Account::~Account()
{
}

const string& Account::GetData(DataType ThisDataType)
{
	switch (ThisDataType)
	{
		case USERNAME:
			return m_username;
		case PASSWORD:
			return m_password;
		case NICKNAME:
			return m_nickname;
	}
}

const bool Account::CheckLogin(string & input1, string & input2)
{
	if (m_username == input1 && m_password == input2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool Account::IsNicknameEmpty() const
{
	return m_nickname.empty();
}

const CallSettings Account::GetCallSetting() const
{
	return m_callSetting;
}

void Account::SetPassword(string & input2)
{
	m_password = input2;
}

void Account::SetNickname(string & input1)
{
	m_nickname = input1;
}

void Account::SetCallSetting(uint16_t temp)
{
	switch (temp)
	{
		case BY_USERNAME:
			m_callSetting = BY_USERNAME;
			cout << "You will be called by your name." << endl;
			break;
		case BY_NICKNAME:
			m_callSetting = BY_NICKNAME;
			cout << "You will be called by your nickname." << endl;
			break;
		default:
			ErrorHandler(INVALID_CHOICE);
			cout << "No changes occurred. you will be called by your name ( Default )." << endl;
			break;
	}
}