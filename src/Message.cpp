#include "Message.h"

Message::Message(string_view sender, string_view topic, string_view message)
{
	m_sender = sender;
	m_topic = topic;
	m_message = message;
}

Message::~Message()
{
}

const string_view Message::GetMSender() const
{
	return m_sender;
}

const string_view Message::GetMTopic() const
{
	return m_topic;
}

const string_view Message::GetM() const
{
	return m_message;
}
