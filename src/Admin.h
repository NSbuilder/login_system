#pragma once
#include "Account.h"

class Admin : public Account
{
public:
	Admin(string_view input1, string& input2);
	~Admin();
	const static unsigned HowManyAdmins();
private:
	static unsigned adminCounter;
};