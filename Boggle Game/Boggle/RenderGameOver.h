#pragma once
#include "RenderTimer.h"
#include "RenderScore.h"
class GameOver
{
private:
	RenderTimer renderTimer;
	RenderScore m_renderScore;
public:

	void displayEndScreen(Score t_score);
};
