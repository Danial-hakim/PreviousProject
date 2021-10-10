#include "RenderRestartOption.h"

std::string RestartOption::displayRestartScreen()
{
	std::cout << restartOption << std::endl;
	std::cout << exitOption << std::endl;

	std::cin >> chosenOption;

	return chosenOption;
}

void RestartOption::invalidInput()
{
	std::cout << invalidInputMessage << std::endl;
}
