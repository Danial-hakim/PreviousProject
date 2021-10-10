//includes
#include "Scoring.h"

void Score::m_processScore(std::string t_word)
{
	m_calculateScore(t_word);
}
void Score::m_calculateScore(std::string t_word)
{
	if (t_word.length() < 3)
	{
		m_playerScore = m_playerScore + 0;
	}
	else if (t_word.length() == 3)
	{
		m_playerScore = m_playerScore + 1;
	}
	else if (t_word.length() == 4)
	{
		m_playerScore = m_playerScore + 1;
	}
	else if (t_word.length() == 5)
	{
		m_playerScore = m_playerScore + 2;
	}
	else if (t_word.length() == 6)
	{
		m_playerScore = m_playerScore + 3;
	}
	else if (t_word.length() == 7)
	{
		m_playerScore = m_playerScore + 4;
	}
	else if (t_word.length() >= 8)
	{
		m_playerScore = m_playerScore + 11;
	}
}

void Score::m_resetScore()
{
	m_playerScore = 0;
}


