#include "Tank.h"
#include <time.h>
Tank::Tank(sf::Texture const& texture, std::vector<sf::Sprite>& t_wallSprites)
	: m_texture(texture)
	, m_wallSprites(t_wallSprites)
{
	srand(time(NULL));
	randomCorner = rand() % 4;
	if (randomCorner == 0)
	{
		currentPosition = { 50.0f,50.0f };
	}
	else if (randomCorner == 1)
	{
		currentPosition = { 50.0f,800.0f };
	}
	else if (randomCorner == 2)
	{
		currentPosition = { 1300.0f,800.0f };
	}
	else 
	{
		currentPosition = { 1300.0f,50.0f };
	}
	m_tankBase.setPosition(currentPosition);
	m_target.setPosition(500, 500);
	initSprites();

	fuelBar.setSize(sf::Vector2f(150, 20));
	fuelBar.setFillColor(sf::Color::Green);
	fuelBar.setPosition(50, 10);

	fuelBarContainer.setSize(sf::Vector2f(150, 20));
	fuelBarContainer.setOutlineColor(sf::Color::Black);
	fuelBarContainer.setOutlineThickness(5.0f);
	fuelBarContainer.setPosition(50, 10);

	fuel.setPosition(400, 400);
}

void Tank::update(double dt)
{	
	randomXPos = rand() % 1000;
	randomYPos = rand() % 700;
	if (isCentreTurret == false)
	{
		/*turretRot = current turret rotation
		tankBaseRot = current tank base rotation*/

			if (m_turretRotation < m_rotation)
			{
				// abs is absolute value
				// in C++, use std::abs()
				if (abs(m_turretRotation - m_rotation ) < 180)
				{
					// Call your increaseTurretRotation() function to increment the turret angle
					increaseTurretRotation();
				}
				else
				{
					decreaseTurretRotation();
				}
			}
			else
			{
				if (abs(m_turretRotation - m_rotation) < 180)
				{
					decreaseTurretRotation();
				}
				else
				{
					increaseTurretRotation();
				}
			}

			isCentreTurret = true;
	}
	handleKeyInput();
	currentPosition.x = currentPosition.x + cos(m_rotation*MathUtility::DEG_TO_RAD) * m_speed * (dt/1000);
	currentPosition.y = currentPosition.y + sin(m_rotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000);
	m_previousPosition = currentPosition;
	m_tankBase.setPosition(currentPosition);
	m_turret.setPosition(currentPosition);
	m_tankBase.setRotation(m_rotation);
	m_turret.setRotation(m_turretRotation + m_rotation);
	m_speed = m_speed * m_friction;
	m_speed = std::clamp(m_speed, MIN_SPEED, MAX_SPEED);

	if (isTargetHit == true)
	{
		m_target.setPosition(randomXPos, randomYPos);
		score = score + 50;
		amountOfTargetHit = amountOfTargetHit + 1;
		accuracy = (amountOfTargetHit / totalShot)*100 ;
		isTargetHit = false;
	}
	checkTargetPosition();
	if (respawnTarget == true)
	{
		m_target.setPosition(randomXPos, randomYPos);
		respawnTarget = false;
	}
	if (checkWallCollision())
	{
		deflect();
		m_enableRotation = true;
	}
	if (m_fireRequested)
	{
		m_shootTimer -= dt;

		if (m_shootTimer <= 0)
		{
			m_shootTimer = s_TIME_BETWEEN_SHOTS;
			m_fireRequested = false;
		}
	}
	m_pool.update(dt, m_wallSprites);

	updateFuelBar();
	respawnFuel();
}

void Tank::render(sf::RenderWindow & window) 
{
	window.draw(m_tankBase);
	window.draw(m_turret);
	window.draw(m_target);
	window.draw(fuelBarContainer);
	window.draw(fuelBar);
	window.draw(fuel);
	m_pool.render(window);
	
}

void Tank::setPosition(sf::Vector2f position)
{
	m_tankBase.setPosition(position);
	m_turret.setPosition(position);
}

void Tank::increaseSpeed()
{
	m_previousSpeed = m_speed;
	if (m_speed < MAX_SPEED)
	{
		m_speed += 1;
	}
}

void Tank::decreaseSpeed()
{
	m_previousSpeed = m_speed;
	if (m_speed > MIN_SPEED)
	{
		m_speed -= 1;
	}
}

void Tank::increaseRotation()
{
	m_previousRotation = m_rotation;
	m_rotation += 1;
	if (m_rotation == 360.0)
	{
		m_rotation = 0;
	}
}

void Tank::decreaseRotation()
{
	m_previousRotation = m_rotation;
	m_rotation -= 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}
}

void Tank::handleKeyInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		increaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		increaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		increaseTurretRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		decreaseTurretRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		centreTurret();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		requestFire();
	}
}

void Tank::increaseTurretRotation()
{
	m_previousTurretRotation = m_turretRotation;
	m_turretRotation += 1;
	if (m_turretRotation == 360.0)
	{
		m_turretRotation = 0;
	}
}

void Tank::decreaseTurretRotation()
{
	m_previousTurretRotation = m_turretRotation;
	m_turretRotation -= 1;
	if (m_turretRotation == 0)
	{
		m_turretRotation = 359;
	}
}

void Tank::centreTurret()
{
	isCentreTurret = false;
}

bool Tank::checkWallCollision()
{
	for (sf::Sprite const& sprite : m_wallSprites)
	{
		// Checks if either the tank base or turret has collided with the current wall sprite.
		if (CollisionDetector::collision(m_turret, sprite) ||
			CollisionDetector::collision(m_tankBase, sprite))
		{
			return true;
		}
	}
	return false;
}



/// If the tank speed is currently 0, the rotation is set to a value that is less than the previous rotation value
///  (scenario: tank is stopped and rotates into a wall, so it gets rotated towards the opposite direction).
/// If the tank is moving, further rotations are disabled and the previous tank position is restored.
/// The tank speed is adjusted so that it will travel slowly in the opposite direction. The tank rotation 
///  is also adjusted as above if necessary (scenario: tank is both moving and rotating, upon wall collision it's 
///  speed is reversed but with a smaller magnitude, while it is rotated in the opposite direction of it's 
///  pre-collision rotation).
void Tank::deflect()
{
	//in case tank was rotating.
	adjustRotation();

	//if tank was moving
	if (m_speed != 0)
	{
		//temporarily disable turret rotation on collision
		m_enableRotation = false;
		//Back up to position in previous frame
		m_tankBase.setPosition(m_previousPosition);
		//Apply small force in opposite direction of travel
		if (m_previousSpeed < 0)
		{
			m_speed = 0;
		}
		else
		{
			m_speed = -8;
		}
	}
}

void Tank::adjustRotation()
{
	//If tank was rotating...
	if (m_rotation != m_previousRotation)
	{
		//work out which direction to rotate the tank base post-collision
		if (m_rotation > m_previousRotation)
		{
			m_rotation = m_previousRotation - 1;
		}
		else
		{
			m_rotation = m_previousRotation + 1;
		}
	}
	//if turret was rotating while tank was moving
	if (m_turretRotation != m_previousTurretRotation)
	{
		//set the turret rotation back to its pre collision value
		m_turretRotation = m_previousTurretRotation;
	}
}

int Tank::getScore()
{
	return score;
}

float Tank::getAccuracy()
{
	return accuracy;
}

sf::Vector2f Tank::getPosition() const
{
	return m_tankBase.getPosition();
}

void Tank::requestFire()
{
	
	m_fireRequested = true;
	if (m_shootTimer == s_TIME_BETWEEN_SHOTS)
	{
		sf::Vector2f tipOfTurret(m_turret.getPosition().x + 2.0f, m_turret.getPosition().y);
		tipOfTurret.x += std::cos(MathUtility::DEG_TO_RAD * m_turret.getRotation()) * ((m_turret.getLocalBounds().top + m_turret.getLocalBounds().height) * 1.7f);
		tipOfTurret.y += std::sin(MathUtility::DEG_TO_RAD * m_turret.getRotation()) * ((m_turret.getLocalBounds().top + m_turret.getLocalBounds().height) * 1.7f);
		m_pool.create(m_texture, tipOfTurret.x, tipOfTurret.y, m_turret.getRotation());
	}
}

sf::Sprite Tank::getTurret() const
{
	return m_turret;
}

sf::Sprite Tank::getBase() const
{
	return m_tankBase;
}

void Tank::initSprites()
{
	// Initialise the tank base
	m_tankBase.setTexture(m_texture);
	sf::IntRect baseRect(2, 43, 79, 43);
	m_tankBase.setTextureRect(baseRect);
	m_tankBase.setScale(0.7, 0.7);
	m_tankBase.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);

	// Initialise the turret
	m_turret.setTexture(m_texture);
	sf::IntRect turretRect(19, 1, 83, 31);
	m_turret.setTextureRect(turretRect);
	m_turret.setScale(0.7, 0.7);
	m_turret.setOrigin(turretRect.width / 3.0, turretRect.height / 2.0);


	if (!targetTexture.loadFromFile("resources/images/target.png"))
	{
		std::cout << "Target texture error" << std::endl;
	}
	m_target.setTexture(targetTexture);
	m_target.setScale(0.1, 0.1);
	m_target.setOrigin(targetTexture.getSize().x / 2, targetTexture.getSize().y / 2);

	if (!fuelTexture.loadFromFile("resources/images/fuel.png"))
	{
		std::cout << "fuel texture error" << std::endl;
	}
	fuel.setTexture(fuelTexture);
	fuel.setScale(0.05, 0.05);
	fuel.setOrigin(fuelTexture.getSize().x / 2, fuelTexture.getSize().y / 2);
}

void Tank::checkTargetPosition()
{
	for (sf::Sprite const& sprite : m_wallSprites)
	{
		// Checks if either the tank base or turret has collided with the current wall sprite.
		if (CollisionDetector::collision(m_target, sprite))
		{
			respawnTarget = true;
		}
	}
}

void Tank::updateFuelBar()
{
	float currentSize = fuelBar.getSize().x;

	if (currentSize <= 0)
	{
		currentSize = 0;
	}
	else if (currentSize > 150)
	{
		currentSize = 150;
	}
	else
	{
		currentSize = currentSize - 0.03;
	}

	fuelBar.setSize(sf::Vector2f(currentSize, 20));
}

void Tank::respawnFuel()
{
	srand(time(NULL));

	sf::Vector2f addFuel{ 5,0 };
	sf::Vector2f currentFuel = fuelBar.getSize();
	float newXPos = 0;
	float newYPos = 0;
	
	if (m_tankBase.getGlobalBounds().intersects(fuel.getGlobalBounds()))
	{
		currentFuel += addFuel;
		
		newXPos = (rand() % 500) + 200;
		newYPos = (rand() % 500) + 200;
		fuel.setPosition(newXPos, newYPos);
	}

	fuelBar.setSize(currentFuel);
	
}
