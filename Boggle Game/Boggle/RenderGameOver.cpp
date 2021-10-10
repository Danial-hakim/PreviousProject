#include "RenderGameOver.h"

void GameOver::displayEndScreen(Score t_score)
{
    // clear screen
    system("CLS");

    renderTimer.displayTimeUp();

    m_renderScore.displayScore(t_score); 
    m_renderScore.displayHighestScore(t_score);
}
