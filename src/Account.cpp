#include "Account.h"
#include "Helper.h"

Account::Account(string_view input1, string& input2)
{
	hash<string> hasher;
	m_username = input1;
	hashedPassword = hasher(input2);
	m_callSetting = NamePreferences::BY_USERNAME;
	accCounter++;
	m_Notes.reserve(25);
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

const NamePreferences Account::GetCallSetting() const
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

void Account::SetCallSetting(NamePreferences temp)
{
	switch (temp)
	{
		case NamePreferences::BY_USERNAME:
			m_callSetting = NamePreferences::BY_USERNAME;
			cout << "You will be called by your name." << endl;
			break;
		case NamePreferences::BY_NICKNAME:
			m_callSetting = NamePreferences::BY_NICKNAME;
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

void Account::NotesSection()
{

}

bool Account::IsThisAGoodMessageIndex(unsigned int i)
{
	return (i <= m_Notes.size());
}

void Account::PrintAllNotes()
{
	string temp;

	for (int i = 0; i < m_Notes.size(); ++i)
	{
		if (m_Notes.at(i).GetNTopic().empty())
		{
			temp = m_Notes.at(i).GetNContent().substr(0, 26);
			cout << "Note " << i + 1 << ": " << temp;

			if (m_Notes.at(i).GetNContent().length() > 26)
			{
				cout << "..." << endl;
			}
			else
			{
				cout << endl;
			}
				
		}
		else
		{
			cout << "Note " << i + 1 << ": " << m_Notes.at(i).GetNTopic() << endl;
		}
			
	}
}

void Account::PrintNote(unsigned int i )
{
	cout << "****" << "Note " << i << "****" << "." << endl << endl;
	cout << "Title: " << m_Notes.at(i-1).GetNTopic() << endl << endl;
	cout << "Content: " << endl << endl << m_Notes.at(i-1).GetNContent() << endl << endl;
	cout << "****" << "Note " << i << "****" << "." << endl << endl;
}

bool Account::NoNotes()
{
	return m_Notes.empty();
}

void Account::EraseNote(unsigned int i)
{
	m_Notes.erase(m_Notes.begin() + (i-1));
}

void Account::InsertNote(Note& newNote)
{
	m_Notes.push_back(newNote);
}

void Account::EditNote(unsigned short i, Note& editNote)
{
	m_Notes.at(i-1) = editNote;
}

queue<Message>& Account::GetMessages()
{
	return m_MessageBox;
}

unsigned Account::accCounter = 0;

//vector<Note>& Account::GetMNotes()
//{
//	return m_Notes;
//}

const unsigned Account::HowManyAccounts()
{
	return accCounter;
}