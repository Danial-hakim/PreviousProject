#include "RenderSecret.h"

void Secret::displaySecret()
{
	system("CLS");
	for (int i = 0; i < 13; i++)
	{
		std::cout << secretText[i] << std::endl;
		while (stringTimer > 0)
		{
			stringTimer = stringTimer - 0.00001;
		}
		stringTimer = TIMERDELAY;
		system("CLS");
	}

}
