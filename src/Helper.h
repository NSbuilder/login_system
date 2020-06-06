#pragma once
#include <iostream>
#include <string>

using namespace std;

void ClrScr(); // Clear the screen

void ScrFriz(); // Wait for input

void SInput(unsigned short& choice); //Receive input to integer and prevent errors

void SInput(string& input, bool ignore = true); //Receive input that contain spaces

enum class ErrType
{
	INVALID_CHOICE = 0x101, USERNAME_LENGTH, TAKEN_USERNAME, PASSWORD_LENGTH, ACCOUNT_NOT_FOUND, WRONG_PASSWORD, UNSAVED_NEW_PASSWORD
};

void ErrHandler(ErrType errNumber);