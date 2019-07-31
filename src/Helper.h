#pragma once
#include <iostream>
#include <limits>
#include <cstdint>
#include <cstdlib>

using namespace std;

inline void Cclear()
{
#ifdef _WIN32
	system("cls");
#else
	system(clear);
#endif
}

inline void Cpause()
{
#ifdef _WIN32
	system("pause");
#else
	cout << "Press enter to continue" << endl;
	cin.get();
#endif
}

void CinToInt(uint16_t& choice);

enum ErrorType
{
	INVALID_CHOICE = 0x101, USERNAME_LENGTH, TAKEN_USERNAME, PASSWORD_LENGTH, ACCOUNT_NOT_FOUND, WRONG_PASSWORD, UNSAVED_NEW_PASSWORD
};

void ErrorHandler(uint16_t errNumber);