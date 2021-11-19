#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "tinyc2.h"
#include "Player.h"
#include "Maths.h"

enum class alienState
{
	PATROLLING,
	CHASING,
	CONFUSE,
	HEARD_NOISE
};

class Alien
{
public:

	Alien(Player* player);

	void init();
	void Draw(sf::RenderWindow& window);
	void update(double dt);

	sf::Vector2f getPos();

	void heardNoise(sf::Vector2f t_noisePos);
	void heardNoise();

private:

	void Patrolling();
	void goingTowardsSound();

	void updateVisionCone();
	sf::Vector2f rotatedVector(const sf::Vector2f& vector, float angle);
	void rotate(sf::Vector2f& vector, float angle);

	bool isPlayerSpotted();
	void movement(double dt);

	sf::Vector2f nextTarget(sf::Vector2f vector);

	sf::Sprite alienSprite;
	sf::Texture alienTexture;

	const sf::Vector2f SCALE_DOWN{ 0.1f, 0.1f };
	float speed;
	bool hasReached;
	sf::Vector2f soundSpot;
	sf::Vector2f direction;

	sf::Vector2f conePointA;
	sf::Vector2f conePointB;
	sf::Vector2f conePointC;

	sf::Vector2f coneDirection{ 1.0f , 0.0f };
	float patrolConeLength{ 400.0f };
	float coneAngle{ 10.0f };
	float MAX_VISION_RANGE{ 20.0f};

	sf::VertexArray visionCone;

	const float PI  { 3.14159265358979323846f };
	const float MAX_SPEED{ 50.0f };
	const float MAX_FORCE{ 10.0f };
	double rotation{ 0.0f };

	std::vector<sf::Vector2f> wayPoints;
	int nextWayPoints = 3;
	sf::Vector2f velocity;

	c2Circle playerCircle;
	c2Poly visionConePoly;
	Player* player;

	alienState currentState;
};
