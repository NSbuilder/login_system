#pragma once
#include <iostream>
#include <string>

using namespace std;

void ClrScr(); // Clear the screen

void ScrFriz(); // Wait for input

void SInput(unsigned short& choice); //Receive input as integer and prevent errors

void SInput(string& input, bool ignore = true); //Deals with receiving inputs that contain spaces
                                                // "ignore = true" unless multiple getlines one after the other
enum class ErrType
{
	INVALID_CHOICE = 0x101, USERNAME_LENGTH, TAKEN_USERNAME, PASSWORD_INVALID_LENGTH, ACCOUNT_NOT_FOUND, WRONG_PASSWORD, UNSAVED_NEW_PASSWORD
};

void ErrHandler(ErrType errNumber);