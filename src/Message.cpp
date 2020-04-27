#include "Message.h"

Message::Message(string& topic, string& message)
{
	topic = topic;
	message = message;
}

Message::~Message()
{

}

string Message::GetMTopic() const
{
	return topic;
}

string Message::GetM() const
{
	return message;
}
