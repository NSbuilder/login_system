#include "Account.h"

Account::Account(string_view input1, string_view input2)
{
	m_username = input1;
	m_password = input2;
	m_callSetting = CallSettings::BY_USERNAME;
}

Account::~Account()
{
}

const string_view Account::GetData(DataType ThisDataType) const
{
	switch (ThisDataType)
	{
	default:case DataType::USERNAME: //
			return m_username;
		case DataType::PASSWORD:
			return m_password;
		case DataType::NICKNAME:
			return m_nickname;
	}
}

const bool Account::FindAcc(string_view input1) const
{
	if (m_username == input1)
	{
		return true;
	}
	
	return false;
}

const bool Account::CheckLogin(string_view input2) const
{
	if (m_password == input2)
	{
		return true;
	}
	
	return false;

}

const bool Account::IsNicknameEmpty() const
{
	return m_nickname.empty();
}

const CallSettings Account::GetCallSetting() const
{
	return m_callSetting;
}

void Account::SetPassword(string_view input2)
{
	m_password = input2;
}

void Account::SetNickname(string_view input1)
{
	m_nickname = input1;
}

void Account::SetCallSetting(CallSettings temp)
{
	switch (temp)
	{
		case CallSettings::BY_USERNAME:
			m_callSetting = CallSettings::BY_USERNAME;
			cout << "You will be called by your name." << endl;
			break;
		case CallSettings::BY_NICKNAME:
			m_callSetting = CallSettings::BY_NICKNAME;
			cout << "You will be called by your nickname." << endl;
			break;
		default:
			ErrHandler(ErrType::INVALID_CHOICE);
			cout << "No changes occurred. you will be called by your name ( Default )." << endl;
			break;
	}
}

void Account::InsertMessage(Message& msg)
{
	m_MessageBox.push(msg);
	cout << "Message sent successfully to " + this->m_username + "." << endl;
	ScrFriz();
}

queue<Message>& Account::GetMessages()
{
	return m_MessageBox;
}