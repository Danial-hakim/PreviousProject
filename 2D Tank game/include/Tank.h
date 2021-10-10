#pragma once
#include <SFML/Graphics.hpp>
#include "MathUtility.h"
#include "CollisionDetector.h"
#include <iostream>
#include <time.h>
#include "ProjectilePool.h"

/// <summary>
/// @brief A simple tank controller.
/// 
/// This class will manage all tank movement and rotations.
/// </summary>
class Tank
{
public:	
	Tank(sf::Texture const & texture, std::vector<sf::Sprite>& t_wallSprites);
	void update(double dt);
	void render(sf::RenderWindow & window);
	void setPosition(sf::Vector2f position);
	void increaseSpeed();
	void decreaseSpeed();
	void increaseRotation();
	void decreaseRotation();
	void handleKeyInput();
	void increaseTurretRotation();
	void decreaseTurretRotation();
	void centreTurret();
	bool checkWallCollision();
	void deflect();
	void adjustRotation();
	int getScore();
	float getAccuracy();
	sf::Vector2f getPosition() const;
	void requestFire();
	sf::Sprite getTurret() const;
	sf::Sprite getBase() const;

private:
	void initSprites();
	sf::Sprite m_tankBase;
	sf::Sprite m_turret;
	sf::Texture const & m_texture;
	double m_speed{ 0.0 };
	double m_rotation{ 0.0 };
	sf::Vector2f currentPosition{};
	double m_friction{ 0.995 };
	const double MAX_SPEED = { 100.0 };
	const double MIN_SPEED = { -100.0 };
	double m_turretRotation{ 0.0 };
	bool isCentreTurret{ true };
	std::vector<sf::Sprite>& m_wallSprites;
	bool m_enableRotation = true;
	sf::Vector2f m_previousPosition;
	double m_previousSpeed;
	double m_previousRotation;
	double m_previousTurretRotation;
	int randomCorner{};

	//pop up target
	sf::Sprite m_target;
	sf::Texture targetTexture;
	bool isTargetHit{ false };
	bool respawnTarget{ false };
	double randomXPos{};
	double randomYPos{};
	void checkTargetPosition();
	float totalShot{ 0 };
	float amountOfTargetHit{ 0 };
	float accuracy{ 0 };

	//Score
	int score{ 0 };

	//ProjectilePool
	ProjectilePool m_pool;

	// The delay time between shots in milliseconds.
	static int const s_TIME_BETWEEN_SHOTS{ 800 };
	bool m_fireRequested;
	int m_shootTimer{ s_TIME_BETWEEN_SHOTS };

	sf::RectangleShape fuelBar;
	sf::RectangleShape fuelBarContainer;
	void updateFuelBar();

	sf::Sprite fuel;
	sf::Texture fuelTexture;
	void respawnFuel();
};
