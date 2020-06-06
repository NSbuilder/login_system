#include "Account.h"
#include "Helper.h"

Account::Account(string_view input1, string& input2)
{
	hash<string> hasher;
	m_username = input1;
	hashedPassword = hasher(input2);
	m_callSetting = CallSettings::BY_USERNAME;
	accCounter++;
}

Account::~Account()
{
	accCounter--;
}

bool Account::TryLogin(string_view input1, string& input2 )
{
	hash<string> hasher;
	size_t hashedTry {hasher(input2)};

	if (input1 == m_username && hashedTry == hashedPassword )
		return true;
	
	return false;
}

const string_view Account::GetData(DataType ThisDataType) const
{
	switch (ThisDataType)
	{
	case DataType::USERNAME:
		return m_username;
	case DataType::NICKNAME:
		return m_nickname;
	default:
		ErrHandler(ErrType::INVALID_CHOICE);
	}
}

const bool Account::GetUsername(string_view input1) const
{
	if (m_username == input1)
	{
		return true;
	}
	
	return false;
}

const bool Account::ValidateLogin(string& input2)
{
	size_t hashedTry;
	hash<string> hasher;
	hashedTry = hasher(input2);

	if (hashedPassword == hashedTry)
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

const bool Account::IsAdmin() const
{
	return isAdmin;
}

void Account::SetPassword(string_view input2)
{
	hash<string> hasher;
	hashedPassword = hasher(static_cast<string>(input2));
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

unsigned Account::accCounter = 0;

const unsigned Account::HowManyAccounts()
{
	return accCounter;
}