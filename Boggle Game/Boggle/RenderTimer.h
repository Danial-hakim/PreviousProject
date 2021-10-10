#pragma once

#include "Timer.h"
#include <iostream>

class RenderTimer
{
private:
	int timeRemaining;
public:
	void drawTimer(Timer timer);
	void displayTimeUp();
};