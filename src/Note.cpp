#include "Note.h"

Note::Note(string_view title, string_view content)
{
	m_title = title;
	m_content = content;
}

Note::~Note()
{

}

const string_view Note::GetNTopic() const
{
	return m_title;
}

const string_view Note::GetNContent() const
{
	return m_content;
}
