#include "RenderGame.h"

void Game::displayGame()
{
    std::srand(time(NULL));

    m_grid.randomiseLetters();

    m_timer.setGameTime(GAME_TIME); // It took a long time to load if you restart the game and player might get less time - Danial 

    m_timer.start();

    // read file to get highest score
    m_readSaveFile.readSaveFile(m_score);

    while (m_timer.elapsedSeconds() < GAME_TIME)
    {
        currentSecond = m_timer.elapsedSeconds();

        // prevents repeat numbers being printed and redrawing game world too often
        if (currentSecond > previousSecond)
        {
            // clear screen
            system("CLS");
            currentSecond = m_timer.elapsedSeconds();

            previousSecond = currentSecond;

            m_renderScore.displayScore(m_score);

            renderTimer.drawTimer(m_timer);

            m_renderGrid.drawBoard(m_grid);

            std::cout << std::endl;

            m_renderUsedWords.renderWords(m_storeUsedWords);

            std::cout << std::endl;

            std::cout << std::endl;

            std::cout << "Please Enter a Word:   ";

            std::cin >> playerWord;

            // I put this into an if statement because this function was being called but we were doing nothing with it,
            // I was able to enter in illegal words while playing the game - Stephen
            if (m_checkword.checkAllConditions(playerWord, m_grid))
            {
                if (m_storeUsedWords.checkIfRepeatWord(playerWord) == false)
                {
                    m_storeUsedWords.addNewWordToArray(playerWord);
                    m_score.m_processScore(playerWord);
                    m_storeUsedWords.addNewWordToArray(playerWord);
                }
            }
            else
            {
                m_checkword.invalidWord();
            }

        }
    }

    m_timer.stop();

    m_storeUsedWords.resetArray();
    // new high score, write it to the file and read the new stored high score value
    if (m_score.m_playerScore > m_score.m_highestPlayerScore)
    {
        m_saveToFile.writeToSaveFile(m_score);
        m_readSaveFile.readSaveFile(m_score);
    }

    m_score.m_resetScore();
}

Score Game::score()
{
    return m_score;
}
