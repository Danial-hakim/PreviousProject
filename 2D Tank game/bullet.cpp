#include "bullet.h"

Bullet::Bullet(sf::Texture const& texture, std::vector<sf::Sprite>& t_wallSprites)
	: m_texture(texture)
	, m_wallSprites(t_wallSprites)
{	
	initSprites();
}

void Bullet::update(double dt , sf::Vector2f turretPosition , double turretRotation)
{
	handleKeyInput();
	if (isShot == false)
	{
		m_bullet.setPosition(turretPosition.x,turretPosition.y);
		m_bullet.setRotation(turretRotation);
		std::cout << m_bullet.getPosition().x << std::endl;
	}
	else
	{
		m_speed = 200;
		currentPosition.x = currentPosition.x + cos(turretRotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000);
		currentPosition.y = currentPosition.y + sin(turretRotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000);
	}
	if (checkWallCollision() == true)
	{
		m_bullet.setPosition(turretPosition);
		m_speed = 0;
	}
	else
	{
		m_bullet.setPosition(currentPosition);
	}
}

void Bullet::render(sf::RenderWindow& window)
{
	window.draw(m_bullet);
}

void Bullet::handleKeyInput()
{
	if (isShot == false)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			isShot = true;
		}
	}
}

bool Bullet::checkWallCollision()
{
	for (sf::Sprite const& sprite : m_wallSprites)
	{
		// Checks if bullet has collided with the current wall sprite.
		if (CollisionDetector::collision(m_bullet, sprite)) 
		{
			return true;
		}
	}
	if ((m_bullet.getPosition().x < 0) ||
	    (m_bullet.getPosition().x > 1440) ||
	    (m_bullet.getPosition().y < 0) ||
	    (m_bullet.getPosition().y > 800))
	{
		return true;
	}
	return false;
}

void Bullet::increaseRotation()
{
	
}

void Bullet::decreaseRotation()
{
}

void Bullet::shoot(sf::Vector2f m_turretPosition, double m_turretRotation , double m_dt)
{
	startingPosition = m_turretPosition;
	m_rotation = m_turretRotation;

	if (isShot == false)
	{
		m_bullet.setPosition(startingPosition);
		m_bullet.setRotation(m_rotation);
		std::cout << m_bullet.getPosition().x << std::endl;
	}
	if (isShot == true)
	{
		currentPosition.x = startingPosition.x + cos(m_rotation * MathUtility::DEG_TO_RAD) * m_speed * (m_dt / 1000);
		currentPosition.y = startingPosition.y + sin(m_rotation * MathUtility::DEG_TO_RAD) * m_speed * (m_dt / 1000);
	}
}

void Bullet::initSprites()
{
	// Initialise the bullet
	m_bullet.setTexture(m_texture);
	sf::IntRect baseRect(2, 175, 12, 15);
	m_bullet.setTextureRect(baseRect);
	m_bullet.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);
	m_bullet.setScale(1.5,1.5);
}
