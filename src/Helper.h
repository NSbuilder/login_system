#pragma once
#include <iostream>

using namespace std;

void ClrScr(); // Clear the screen

void ScrFriz(); // Wait for input

void IntPut(unsigned short& choice); //Receive input to integer and prevent errors

enum class ErrType
{
	INVALID_CHOICE = 0x101, USERNAME_LENGTH, TAKEN_USERNAME, PASSWORD_LENGTH, ACCOUNT_NOT_FOUND, WRONG_PASSWORD, UNSAVED_NEW_PASSWORD
};

void ErrHandler(ErrType errNumber);