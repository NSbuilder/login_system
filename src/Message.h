#pragma once
#include <string>
using namespace std;
class Message
{
public:
	Message(string& sender, string& topic, string& message);
	~Message();
	string GetMSender() const;
	string GetMTopic() const;
	string GetM() const;
private:
	string m_topic;
	string m_message;
	string m_sender;
};

