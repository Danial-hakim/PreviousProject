#include "RenderTimer.h"

void RenderTimer::drawTimer(Timer timer)
{

	timeRemaining = timer.convertToCountDown();

	std::cout << "Time Remaining: " << timeRemaining << std::endl;
}

void RenderTimer::displayTimeUp()
{
	std::cout << "You've Run Out of Time!" << std::endl;
}
