#pragma once
#include <string>
using namespace std;
class Message
{
public:
	Message( string& topic, string& message );
	~Message();
	string GetMTopic() const;
	string GetM() const;
private:
	string topic;
	string message;


};

