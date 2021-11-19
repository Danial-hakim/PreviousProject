#include "Alien.h"

Alien::Alien(Player* T_player)
{
	player = T_player;
}

void Alien::init()
{
	if (!alienTexture.loadFromFile("./Assets/Alien.PNG"))
	{
		std::cout << "Error with alienSprite" << std::endl;
	}
	alienSprite.setTexture(alienTexture);
	alienSprite.setScale(SCALE_DOWN);
	alienSprite.setOrigin(alienTexture.getSize().x / 2.0f, alienTexture.getSize().y / 2.0f);
	alienSprite.setPosition(400, 126);

	currentState = alienState::PATROLLING;
	wayPoints.push_back(sf::Vector2f(600,300)); // 3
	wayPoints.push_back(sf::Vector2f(800, 600));
	wayPoints.push_back(sf::Vector2f(300, 600));
	wayPoints.push_back(sf::Vector2f(800, 300)); // 0
}

void Alien::Draw(sf::RenderWindow& window)
{
	window.draw(alienSprite);
	window.draw(visionCone);
}

void Alien::update(double dt)
{
	switch (currentState)
	{
	case alienState::PATROLLING:

		direction += Maths::unitVector(nextTarget(wayPoints[nextWayPoints]));
		velocity = Maths::truncate(velocity + direction, MAX_SPEED);
		Patrolling();

		break;
	case alienState::CHASING:

		direction += Maths::unitVector(nextTarget(player->getPos()));
		direction = Maths::truncate(direction, MAX_FORCE);
		velocity = Maths::truncate(velocity + direction, MAX_SPEED);

		break;
	case alienState::CONFUSE:

		std::cout << "Confuse" << std::endl;
		currentState = alienState::PATROLLING;
		std::cout << "Back to patrol" << std::endl;
		break;

	case alienState::HEARD_NOISE:
		direction += Maths::unitVector(nextTarget(soundSpot));
		velocity = Maths::truncate(velocity + direction, MAX_SPEED);
		goingTowardsSound();
	default:
		break;

	}

	auto dest = atan2(-1 * velocity.y, -1 * velocity.x) / PI * 180 + 180;
	if (currentState == alienState::CONFUSE)
	{
		dest *= -1;
	}
	auto currentRotation = rotation;

	if (std::round(currentRotation - dest) == 0.0)
	{
		direction.x = 0;
		direction.y = 0;
	}
	else if ((static_cast<int>(std::round(dest - currentRotation + 360))) % 360 < 180)
	{
		rotation = static_cast<int>((rotation)+1) % 360;
	}
	else
	{
		rotation = static_cast<int>((rotation)-1) % 360;
	}

	updateVisionCone();
	if (isPlayerSpotted()) 
	{
		currentState = alienState::CHASING;
	}

	else if(!isPlayerSpotted() && currentState == alienState::CHASING)
	{
		currentState = alienState::CONFUSE;
	}
	movement(dt);
}

void Alien::updateVisionCone()
{
	visionCone = sf::VertexArray(sf::Triangles, 3);

	conePointA = alienSprite.getPosition();
	conePointB = alienSprite.getPosition() + patrolConeLength * rotatedVector(coneDirection, -coneAngle + alienSprite.getRotation());
	conePointC = alienSprite.getPosition() + patrolConeLength * rotatedVector(coneDirection, coneAngle + alienSprite.getRotation());

	visionCone[0].position = conePointA;
	visionCone[1].position = conePointB;
	visionCone[2].position = conePointC;

	visionCone[0].color = sf::Color::Red;
	visionCone[1].color = sf::Color::Transparent;
	visionCone[2].color = sf::Color::Transparent;
}

sf::Vector2f Alien::rotatedVector(const sf::Vector2f& vector, float angle)
{
	sf::Vector2f copy = vector;
	rotate(copy, angle);
	return copy;
}

void Alien::rotate(sf::Vector2f& vector, float angle)
{
	float cos = std::cos(angle* PI/180);
	float sin = std::sin(angle* PI/180);

	vector = sf::Vector2f(
		cos * vector.x - sin * vector.y,
		sin * vector.x + cos * vector.y);
}
sf::Vector2f Alien::getPos()
{
	return alienSprite.getPosition();
}
void Alien::heardNoise(sf::Vector2f t_noisePos)
{
	soundSpot = t_noisePos;
	currentState = alienState::HEARD_NOISE;
}

void Alien::heardNoise()
{
	soundSpot = player->getPos();
	currentState = alienState::HEARD_NOISE;
}

bool Alien::isPlayerSpotted()
{
	playerCircle.r = 15.0f;

	playerCircle.p.x = player->getPos().x;
	playerCircle.p.y = player->getPos().y;

	visionConePoly.count = 3;

	visionConePoly.verts[0] = c2v{ conePointA.x,conePointA.y };
	visionConePoly.verts[1] = c2v{ conePointB.x,conePointB.y };
	visionConePoly.verts[2] = c2v{ conePointC.x,conePointC.y };

	int result = c2CircletoPoly(playerCircle, &visionConePoly, NULL);

	return result != 0;
}

void Alien::Patrolling()
{
	int result = Maths::distance(alienSprite.getPosition(), wayPoints[nextWayPoints]);
	
	if (result < 10)
	{
		nextWayPoints = (nextWayPoints + 1) % wayPoints.size();
	}
}

void Alien::goingTowardsSound()
{
	int result = Maths::distance(alienSprite.getPosition(), soundSpot);

	if (result < 10)
	{
		currentState = alienState::CONFUSE;
	}
}

void Alien::movement(double dt) 
{
	double speed = Maths::length(velocity);
	sf::Vector2f newPos(alienSprite.getPosition().x + std::cos((PI / 180) * rotation) * speed * (dt / 1000),
						alienSprite.getPosition().y + std::sin((PI / 180) * rotation) * speed * (dt / 1000));
	alienSprite.setPosition(newPos);
	alienSprite.setRotation(rotation);
}

sf::Vector2f Alien::nextTarget(sf::Vector2f vector)
{
	return vector - alienSprite.getPosition();
}

