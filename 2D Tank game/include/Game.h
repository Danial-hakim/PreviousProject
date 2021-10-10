#pragma once

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"

#include "LevelLoader.h"

#include "Tank.h"
#include "TankAI.h"

#include "GameState.h"
#include "HUD.h"

/// <summary>
/// @author Danial Hakim
/// @date September 2020
/// @version 1.0
/// 
/// </summary>

/// <summary>
/// @brief Main class for the SFML Playground project.
/// 
/// This will be a single class framework for learning about SFML. 
/// Example usage:
///		Game game;
///		game.run();
/// </summary>

class Game
{

	

public:
	/// <summary>
	/// @brief Default constructor that initialises the SFML window, 
	///   and sets vertical sync enabled. 
	/// </summary>
	Game();

	/// <summary>
	/// @brief the main game loop.
	/// 
	/// A complete loop involves processing SFML events, updating and drawing all game objects.
	/// The actual elapsed time for a single game loop results (lag) is stored. If this value is 
	///  greater than the notional time for one loop (MS_PER_UPDATE), then additional updates will be 
	///  performed until the lag is less than the notional time for one loop.
	/// The target is one update and one render cycle per game loop, but slower PCs may 
	///  perform more update than render operations in one loop.
	/// </summary>
	void run();
	
	
protected:
	/// <summary>
	/// @brief Placeholder to perform updates to all game objects.
	/// </summary>
	/// <param name="time">update delta time</param>
	void update(double dt);

	/// <summary>
	/// @brief Draws the background and foreground game objects in the SFML window.
	/// The render window is always cleared to black before anything is drawn.
	/// </summary>
	void render();

	/// <summary>
	/// @brief Checks for events.
	/// Allows window to function and exit. 
	/// Events are passed on to the Game::processGameEvents() method.
	/// </summary>	
	void processEvents();

	/// <summary>
	/// @brief Handles all user input.
	/// </summary>
	/// <param name="event">system event</param>
	void processGameEvents(sf::Event&);

	// main window
	sf::RenderWindow m_window;

	LevelData m_level;

	std::vector<sf::Sprite> m_spriteVector;
	sf::Texture m_texture;
	
	sf::Sprite m_bgSprite;
	sf::Texture m_bgTexture;

	std::vector<sf::Sprite>m_wallSprites;
	
	sf::Text timerText;
	sf::Text scoreText;
	sf::Text accuracytext;
	sf::Font font;

	int timer{ 60 };
	int score{ 0 };
	int accuracy{ 0 };
	float OneSecondCounter{ 178 }; // it has no limiter so refresh at higher rate?

	void generateWalls();

	//an instance representing the player control tank
	Tank m_tank;

	//an instance representing the AI control tank
	TankAi m_aiTank;

	// The initial game state set to GAME_RUNNING
	GameState m_gameState{ GameState::GAME_RUNNING };

	// The font to be used for the HUD.
	sf::Font m_font;

	// The game HUD instance.
	HUD m_hud;
};
