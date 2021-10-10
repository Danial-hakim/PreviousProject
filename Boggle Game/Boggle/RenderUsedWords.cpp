#include "RenderUsedWords.h"

void RenderUsedWords::renderWords(StoreUsedWords t_workStorage)
{
	for (int index = 0; index < t_workStorage.MAX_WORDS; index++)
	{
		std::cout << "    <- " << t_workStorage.m_words[index] << " ->     ";
	}
}
