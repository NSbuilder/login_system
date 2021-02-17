#pragma once

#include <string>
#include <string_view>

using namespace std;

class Note
{
public:
	Note(string_view title, string_view content);
	~Note();
	const string_view GetNTopic() const;
	const string_view GetNContent() const;

private:
	string m_title;
	string m_content;
};

