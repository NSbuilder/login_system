#include "Admin.h"

Admin::Admin(string_view input1, string_view input2) : Account(input1, input2)
{
	isAdmin = true;
	adminCounter++;
}

Admin::~Admin()
{
	adminCounter--;
}

unsigned Admin::adminCounter = 0;

const unsigned Admin::HowManyAdmins()
{
	return adminCounter;
}
