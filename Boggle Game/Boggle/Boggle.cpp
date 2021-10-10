// Boggle.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>

#include "RenderMenu.h"
#include "RenderGame.h"
#include "RenderGameOver.h"
#include "RenderInstructions.h"
#include "RenderSecret.h"
#include "RenderRestartOption.h"

enum class GameState
{
	Menu,
	Game,
	Instructions,
	GameOver,
	Restart,
	Secret
};


int main()
{
	Menu m_menu;
	Game m_game;
	GameOver m_end;
	Instructions m_instruc;
	Secret m_secret;
	RestartOption m_restart;

	GameState m_currentState = GameState::Menu;
	std::string chosenOption;
	std::string restartOption;
	bool gameInProgress = true;

	while (gameInProgress)
	{
		switch (m_currentState)
		{
		case GameState::Menu:
			system("Color 5");
			m_menu.displayText();
			std::cin >> chosenOption;
			if (chosenOption == "0")
			{
				//closes window
				gameInProgress = false;
			}
			else if (chosenOption == "1")
			{
				//starts game
				m_currentState = GameState::Game;
			}
			else if (chosenOption == "2")
			{
				//shows instructions
				m_currentState = GameState::Instructions;
			}
			else if (chosenOption == "ESCAPE")
			{
				system("Color 4");
				//displays a secret screen
				m_secret.displaySecret();
				m_currentState = GameState::Game;
			}
			else
			{
				//if string entered is not an option, player can try again
				std::cout << "Option not identified" << std::endl;
				m_currentState = GameState::Menu;
				// clear screen
				system("CLS");
			}
			break;
		case GameState::Game:
			system("Color 3");
			m_game.displayGame();
			m_currentState = GameState::GameOver;
			break;
		case GameState::GameOver:
			system("Color 6");
			m_end.displayEndScreen(m_game.score());
			m_currentState = GameState::Restart;
			break;
		case GameState::Restart:
			restartOption = m_restart.displayRestartScreen();
			system("CLS");
			if (restartOption == "1")
			{
				chosenOption = "";
				m_currentState = GameState::Menu;
			}
			else if (restartOption == "2")
			{
				gameInProgress = false;
			}
			else
			{
				m_restart.invalidInput();
				m_currentState = GameState::Restart;
			}
			break;
		case GameState::Instructions:
			system("Color 2");
			m_instruc.displayInstruc();

			std::cin >> chosenOption;
			if (chosenOption == "0")
			{
				//closes window
				gameInProgress = false;
			}
			else if (chosenOption == "1")
			{
				//starts game
				m_currentState = GameState::Game;
			}
			else if (chosenOption == "ESCAPE")
			{
				system("Color 4");
				//displays a secret screen
				m_secret.displaySecret();
				m_currentState = GameState::Game;
			}
			else
			{
				//if string entered is not an option, player can try again
				std::cout << "Option not identified" << std::endl;
				m_currentState = GameState::Instructions;
				// clear screen
				system("CLS");
			}
			break;
		default:
			break;
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
