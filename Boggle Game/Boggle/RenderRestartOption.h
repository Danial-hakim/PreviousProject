#pragma once
#include <iostream>
#include "StoreUsedWords.h"

class RestartOption
{
private:

	std::string restartOption = "Press 1 to restart the game ";
	std::string exitOption = "Press 2 to exit the game ";
	std::string invalidInputMessage = "The input is invalid \n Please try again";

	std::string chosenOption;

public:

	std::string displayRestartScreen();
	void invalidInput();

};