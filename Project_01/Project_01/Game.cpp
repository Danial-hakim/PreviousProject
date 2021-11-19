#include "Game.h"
#include <iostream>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "SFML Playground", sf::Style::Default),
	itemsOnFloor(&alien, &grid), player(&itemsOnFloor), alien(&player)
{
	if (!gameFont.loadFromFile("Assets/Fonts/arial.ttf"))
	{
		std::cout << "Unable to load font." << std::endl;
	}

	m_window.setVerticalSyncEnabled(true);
	grid.init();
	player.init(&gameFont);
	alien.init();
	AlienHearing::storeAlienRef(&alien);
}

////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		//sf::Time dt = clock.restart();

		//lag += dt.asMilliseconds();

		processEvents();

		timeSinceLastUpdate += clock.restart();

		//while (lag > MS_PER_UPDATE)
		//{
		//	update(lag);
		//	lag -= MS_PER_UPDATE;
		//}
		//update(lag);

		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame.asMicroseconds() / 500);
		}

		render();
	}




	//while (m_window.isOpen())
	//{
	//	processEvents();
	//	timeSinceLastUpdate += clock.restart();
	//	while (timeSinceLastUpdate > timePerFrame)
	//	{
	//		timeSinceLastUpdate -= timePerFrame;
	//		processEvents();
	//		update(timePerFrame.asSeconds());
	//	}
	//	render();
	//}
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
	if (sf::Event::KeyPressed == event.type || sf::Event::KeyReleased == event.type
		|| event.type == sf::Event::MouseButtonPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		default:
			break;
		}

		player.checkDelayedInput(event);
	}
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{
	SoundManager::update();
	player.Update(collisionHandler.player_Boundary(grid, player));	
	alien.update(dt);
	grid.update(dt);
}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	grid.draw(m_window);

	itemsOnFloor.render(m_window);

	alien.Draw(m_window);
	player.Draw(m_window);

	m_window.display();
}





