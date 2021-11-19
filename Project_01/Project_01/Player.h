#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Maths.h"
#include "Inventory.h"

enum class STATE
{
	CROUCHING,
	WALKING,
	RUNNING
};

class Player
{
public:

	Player(ScannerObserver* t_observer);
	void init(sf::Font* t_font);
	void Draw(sf::RenderWindow& window);
	void Update(bool nearWall);

	void checkInput(bool nearWall);

	void checkDelayedInput(sf::Event& event);
	sf::Vector2f getPos();
	sf::Vector2f getSize();

	void updateMovement();

	Inventory* getInventory();
private:

	Inventory playersInventory;

	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	//float speed = 0;
	
	const sf::Vector2f SCALE_DOWN{ 0.1f,0.1f };
	sf::Vector2f direction;

	const float RUNNINGSPEED{ 6 };
	const float CROUCHINGSPEED{ 0.5 };
	const float WALKINGSPEED{ 3 };
	const float radiantOffSet{ 180.0f };
	sf::Vector2f lastPos;
	sf::Vector2f offset;
	STATE state;
};
