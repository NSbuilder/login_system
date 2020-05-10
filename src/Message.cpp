#include "Message.h"

Message::Message(string& sender, string& topic, string& message)
{
	m_sender = sender;
	m_topic = topic;
	m_message = message;
}

Message::~Message()
{
}

string Message::GetMSender() const
{
	return m_sender;
}

string Message::GetMTopic() const
{
	return m_topic;
}

string Message::GetM() const
{
	return m_message;
}
