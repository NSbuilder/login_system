#include "Message.h"

Message::Message(string_view sender, string_view message, string_view topic)
{
	m_sender = sender;
	m_message = message;
	m_topic = topic;
}

Message::~Message()
{
}

const string_view Message::GetMsgSender() const
{
	return m_sender;
}

const string_view Message::GetMTopic() const
{
	return m_topic;
}

const string_view Message::GetMsg() const
{
	return m_message;
}