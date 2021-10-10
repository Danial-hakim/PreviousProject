#include "RenderScore.h"

void RenderScore::displayScore(Score t_playerScore)
{
	std::cout << "                                                                                                      "
	<< "Total Score: " << t_playerScore.m_playerScore << std::endl;
}

void RenderScore::displayHighestScore(Score t_playerScore)
{
	std::cout << "                                                                                                      "
		<< "High Score: " << t_playerScore.m_highestPlayerScore << std::endl;
}
