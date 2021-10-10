#pragma once
#include <iostream>
/// <summary>
/// an easter egg that pops up only if a particular word is entered
/// </summary>
class Secret
{
private:
	const double TIMERDELAY = 5000;
	//a timer that will send the messages with a delay
	double stringTimer = TIMERDELAY;
	std::string secretText[13] = { "wake up","WAKE UP","THIS IS A SIMULATION","IT'S COMING","DON'T LISTEN TO IT",
		"IT'S WATCHING","THEY MISS YOU","...","why do you run","god can't save you now","may the odds be forever in your favour",
		"sic semper tyrannis","Rebooting internal systems..." };

public:
	void displaySecret();

};
