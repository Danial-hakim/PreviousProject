#include "Game.h"
#include <iostream>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "SFML Playground", sf::Style::Default)
	, m_tank(m_texture, m_wallSprites)
	, m_aiTank(m_texture, m_wallSprites)
	, m_hud(m_font)
{
	int currentLevel = 1;

	try
	{
		LevelLoader::load(currentLevel, m_level);
	}
	catch (std::exception & e)
	{
		std::cout << "Level Loading Failure." << std::endl;
		std::cout << e.what() << std::endl;
		throw e;
	}
	m_window.setVerticalSyncEnabled(true);
	//For background
	if (!m_bgTexture.loadFromFile("./resources/images/Background.jpg"))
	{
		std::string errorMsg("Error loading texture");
		throw std::exception(errorMsg.c_str());
	}
	m_bgSprite.setTexture(m_bgTexture);
	// Load the player tank
	if (!m_texture.loadFromFile("./resources/images/SpriteSheet.png"))
	{
		std::string errorMsg("Error loading texture");
		throw std::exception(errorMsg.c_str());
	}
	//Tank position 
	m_tank.setPosition(m_level.m_tank.m_position);
	//generate walls 
	generateWalls();

	//The text used in game
	if (!font.loadFromFile("./resources/fonts/arial.ttf"))
	{

		// error...

	}

	scoreText.setFont(font);
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(1100, 50);

	timerText.setFont(font);
	timerText.setString("Time remaing: " + std::to_string(timer));
	timerText.setCharacterSize(50);
	timerText.setFillColor(sf::Color::White);
	timerText.setPosition(400, 50);

	accuracytext.setFont(font);
	accuracytext.setString("Accuracy: " + std::to_string(accuracy));
	accuracytext.setCharacterSize(50);
	accuracytext.setFillColor(sf::Color::White);
	accuracytext.setPosition(0, 50);

	//Populate the obstacle list and set the AI tank position
	m_aiTank.init(m_level.m_aiTank.m_position);

	if (!m_font.loadFromFile("./resources/fonts/arial.ttf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
}

////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(lag);
			lag -= MS_PER_UPDATE;
		}
		update(lag);

		render();
	}
}

////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

////////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
			case sf::Keyboard::Escape:
				m_window.close();
				break;
			default:
				break;
		}
	}
}

void Game::generateWalls()
{
	sf::IntRect wallRect(2, 129, 33, 23);
	//Create the walls
	for (ObstacleData const& obstacle : m_level.m_obstacles)
	{
		sf::Sprite sprite;
		sprite.setTexture(m_texture);
		sprite.setTextureRect(wallRect);
		sprite.setOrigin(wallRect.width / 2.0, wallRect.height / 2.0);
		sprite.setPosition(obstacle.m_position);
		sprite.setRotation(obstacle.m_rotation);
		m_wallSprites.push_back(sprite);
	}
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{
	/*m_funcApplyDamage = std::bind(&TankAi::applyDamage, m_aiTank, _1);

    m_funcApplyDamage = std::bind(&TankAi::applyDamage, &m_aiTank, _1);*/
	switch (m_gameState)
	{
	case GameState::GAME_RUNNING:
		m_tank.update(dt);
		m_aiTank.update(m_tank, dt);
		break;	
	case GameState::GAME_LOSE:
		break;
	default:
		break;
	}
	if (m_aiTank.collidesWithPlayer(m_tank) == true)
	{
		m_gameState = GameState::GAME_LOSE;
	}
	m_hud.update(m_gameState);

	if (OneSecondCounter <= 0)
	{
		timer--;
		timerText.setString("Time remaing: " + std::to_string(timer));
		OneSecondCounter = 178;
	}
	else
	{
		OneSecondCounter--;
	}
	score = m_tank.getScore();
	scoreText.setString("Score: " + std::to_string(score));

	accuracy = m_tank.getAccuracy();
	accuracytext.setString("Accuracy: " + std::to_string(accuracy));

	
	
}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	m_window.draw(m_bgSprite);
	m_tank.render(m_window);
	m_aiTank.render(m_window);
	m_window.draw(timerText);
	m_window.draw(scoreText);
	m_window.draw(accuracytext);
	m_hud.render(m_window);
	// Render your sprites here....
	for (int i = 0; i < m_wallSprites.size(); i++)
	{
		m_window.draw(m_wallSprites.at(i));
	}

	m_window.display();
}





