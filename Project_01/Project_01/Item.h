#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "ScreenSize.h"
#include "Cell.h"

enum class ItemType
{
	DEFAULT,
	SMOKE_BOMB,
	NOISE_MAKER,
	SCANNER,
	BOOK
};

std::ostream& operator << (std::ostream& strm, const ItemType tt);

class Item
{
protected:
	sf::Texture m_bodyTexture;
	sf::Sprite m_itemBody;
	std::vector<sf::CircleShape> dots;
	ItemType type;

	bool onMap = false;
	bool pickedUp = false;
	bool usedUp = false;
	sf::Vector2f mapPosition;

	const int ANGLE = 90;
	sf::Vector2f velocity;
	float speed{0};


	void initialise(ItemType t_type);

public:
	static float cellWidth;
	static float cellHeight;

	Item(ItemType t_type);
	Item(ItemType t_type, sf::Vector2f t_position);

	virtual void useItem() = 0;
	virtual void update() = 0;

	bool shouldBeDeleted();

	ItemType getItemType();
	virtual void pickUpItem();
	sf::Sprite getBody();
	sf::Vector2f getMapPos();

	void moveBody(sf::Vector2f newPos);

	bool inInventory();

	virtual void renderInInventory(sf::RenderWindow& t_window);
	virtual void renderOnGrid(sf::RenderWindow& t_window);
};

