#include "StoreUsedWords.h"

void StoreUsedWords::addNewWordToArray(std::string t_word)
{
	if (index < MAX_WORDS)
	{
		if (checkIfRepeatWord(t_word) == false)
		{
			m_words[index].assign(t_word);
			index++;
		}
	}
}

bool StoreUsedWords::checkIfRepeatWord(std::string t_word)
{
	for (int counter = 0; counter < MAX_WORDS; counter++)
	{
		if (m_words[counter] == t_word)
		{
			return true;
		}
	}
	return false;
}

void StoreUsedWords::resetArray()
{
	m_words = { "","","","","",
			   "","","","","",
			   "","","","","",
			   "","","","","",
			   "","","","","",
			   "","","","","" };
}
