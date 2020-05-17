#pragma once
#include <string>
#include <string_view>

using namespace std;

class Message
{
public:
	Message(string_view sender, string_view topic, string_view message);
	~Message();
	const string_view GetMSender() const;
	const string_view GetMTopic() const;
	const string_view GetM() const;
private:
	string m_topic;
	string m_message;
	string m_sender;
};

