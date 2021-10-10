#include "RenderInstructions.h"

void Instructions::displayInstruc()
{
	system("CLS");
	for (int i = 0; i < 5; i++)
	{
		std::cout << m_instruc[i] << std::endl;
	}
}
