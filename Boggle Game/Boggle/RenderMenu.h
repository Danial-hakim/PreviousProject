#pragma once
#include <iostream>
class Menu
{

private:
	std::string menuText = "Welcome to Boggle!\nPlease select an option:\n0-Exit Game   1-Start Game   2-Show Instructions";
public:
	void displayText();
};
