#pragma once
#include <string_view>

using namespace std;

class Message
{
public:
	Message(string_view sender, string_view message, string_view topic = "");
	~Message();
	const string_view GetMSender() const;
	const string_view GetMTopic() const;
	const string_view GetM() const;
private:
	string m_topic;
	string m_message;
	string m_sender;
};

