#pragma once
#include "Timer.h"
#include "RenderTimer.h"
#include "Grid.h"
#include "RenderGrid.h"
#include "RenderUsedWords.h"
#include "RenderScore.h"
#include "StoreUsedWords.h"
#include "checkWord.h"
#include "SaveToFile.h"
#include "ReadSaveFile.h"

class Game
{
private:

    // time game has until game over (in seconds)
   // value is low for testing, will be 180 in actual game
    const int GAME_TIME = 180;

    int previousSecond = 0;
    int currentSecond = 0;
    bool wordEntered = false;
    std::string playerWord;

    StoreUsedWords m_storeUsedWords;
    RenderUsedWords m_renderUsedWords;

    Grid m_grid;
    RenderGrid m_renderGrid;

    Timer m_timer;
    RenderTimer renderTimer;

    Score m_score;
    RenderScore m_renderScore;

    ReadSaveFile m_readSaveFile;
    SaveToFile m_saveToFile;

    checkWord m_checkword;

public:
	void displayGame();

    Score score();
};
