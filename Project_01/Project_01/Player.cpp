#include "Player.h"

Player::Player(ScannerObserver* t_observer) : playersInventory(t_observer)
{

}

void Player::init(sf::Font* t_font)
{
	if (!playerTexture.loadFromFile("./Assets/Player.PNG"))
	{
		std::cout << "Error with playerSprite" << std::endl;
	}
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(SCALE_DOWN);
	offset = sf::Vector2f{ playerTexture.getSize().x / 2.0f, playerTexture.getSize().y / 2.0f };
	playerSprite.setOrigin(offset);
	playerSprite.setPosition(120,126);

	playersInventory.getFont(t_font);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(playerSprite);
	playersInventory.render(window);
}

void Player::Update(bool nearWall)
{
	if (!playersInventory.inventoryIsOpen())
	{
		checkInput(nearWall);
		updateMovement();
	}

	playersInventory.update();
}

void Player::checkInput(bool nearWall)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		state = STATE::RUNNING;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
	{
		direction.y = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
	{
		direction.y = 1;
	}
	else
	{
		direction.y = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
	{
		direction.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		direction.x = 1;
	}
	else
	{
		direction.x = 0;
	}
	
	if (nearWall)
	{
		playerSprite.setPosition(lastPos);
	}
	lastPos = playerSprite.getPosition();
}

void Player::checkDelayedInput(sf::Event& event)
{
	playersInventory.handleKeyInventoryInput(event, playerSprite.getPosition(), playerSprite.getRotation() + 180);
}

sf::Vector2f Player::getPos()
{
	return playerSprite.getPosition();
}

sf::Vector2f Player::getSize()
{
	return sf::Vector2f(playerSprite.getTexture()->getSize());
}

void Player::updateMovement()
{
	float radiant = atan2f(direction.y, direction.x);
	float degree = radiant * (radiantOffSet / M_PI) + radiantOffSet;

	if (direction.x != 0 || direction.y != 0)
	{
		playerSprite.setRotation(degree);
	}

	direction = Maths::unitVector(direction);
	playerSprite.move(direction * WALKINGSPEED);

}

Inventory* Player::getInventory()
{
	return &playersInventory;
}
