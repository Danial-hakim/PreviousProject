#include "TankAi.h"

////////////////////////////////////////////////////////////
TankAi::TankAi(sf::Texture const & texture, std::vector<sf::Sprite> & wallSprites)
	: m_aiBehaviour(AiBehaviour::PATROL_MAP)
	, m_texture(texture)
	, m_wallSprites(wallSprites)
	, m_steering(0, 0)
{
	// Initialises the tank base and turret sprites.
	initSprites();
	m_wayPoints.push_back(sf::Vector2f(700, 700));
	m_wayPoints.push_back(sf::Vector2f(900, 700));
	m_wayPoints.push_back(sf::Vector2f(900, 400));
	m_wayPoints.push_back(sf::Vector2f(700, 400));
}

////////////////////////////////////////////////////////////
void TankAi::update(Tank const & playerTank, double dt)
{
	sf::Vector2f vectorToPlayer = seek(playerTank.getPosition());

	m_steering += collisionAvoidance();

	switch (m_aiBehaviour)
	{
	case AiBehaviour::ATTACK_PLAYER:

		m_steering += thor::unitVector(vectorToPlayer);
		m_steering = MathUtility::truncate(m_steering, MAX_FORCE);
		m_velocity = MathUtility::truncate(m_velocity + m_steering, MAX_SPEED);

		break;
	case AiBehaviour::STOP:
		m_velocity = sf::Vector2f(0, 0);
		break;
	case AiBehaviour::PATROL_MAP:
		
		m_steering += thor::unitVector(seek(m_wayPoints[m_nextWayPoint]));
		m_velocity = MathUtility::truncate(m_velocity + m_steering, MAX_SPEED);
		PatrolMap();

		break;
	default:
		break;
	}
	
	// Now we need to convert our velocity vector into a rotation angle between 0 and 359 degrees.
	// The m_velocity vector works like this: vector(1,0) is 0 degrees, while vector(0, 1) is 90 degrees.
	// So for example, 223 degrees would be a clockwise offset from 0 degrees (i.e. along x axis).
	// Note: we add 180 degrees below to convert the final angle into a range 0 to 359 instead of -PI to +PI
	auto dest = atan2(-1 * m_velocity.y, -1 * m_velocity.x) / thor::Pi * 180 + 180;

	auto currentRotation = m_rotation;

	// Find the shortest way to rotate towards the player (clockwise or anti-clockwise)
	if (std::round(currentRotation - dest) == 0.0)
	{
		m_steering.x = 0;
		m_steering.y = 0;
	}

	else if ((static_cast<int>(std::round(dest - currentRotation + 360))) % 360 < 180)
	{
		// rotate clockwise
		m_rotation = static_cast<int>((m_rotation) + 1) % 360;
	}
	else
	{
		// rotate anti-clockwise
		m_rotation = static_cast<int>((m_rotation) - 1) % 360;
	}


	if (thor::length(vectorToPlayer) < MAX_SEE_AHEAD)
	{
		m_aiBehaviour = AiBehaviour::STOP;
	}
	else
	{
		//m_aiBehaviour = AiBehaviour::SEEK_PLAYER;
	}

	updateMovement(dt);
	isPlayerInCone(m_turret.getPosition(), arrowLeftPoints, arrowRightPoints, playerTank);
	visionConeBehavior(playerTank);
	visionConeRotation();
}

////////////////////////////////////////////////////////////
void TankAi::render(sf::RenderWindow & window)
{
	// TODO: Don't draw if off-screen...
	window.draw(m_tankBase);
	window.draw(m_turret);
	window.draw(m_arrowRight);
	window.draw(m_arrowLeft);
}

////////////////////////////////////////////////////////////
void TankAi::init(sf::Vector2f position)
{
	m_tankBase.setPosition(position);
	m_turret.setPosition(position);

	for (sf::Sprite const wallSprite : m_wallSprites)
	{
		sf::CircleShape circle(wallSprite.getTextureRect().width * 1.2f);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(wallSprite.getPosition());
		m_obstacles.push_back(circle);
	}
}

////////////////////////////////////////////////////////////
sf::Vector2f TankAi::seek(sf::Vector2f currentTargetWaypoints) const
{
	// This line is simply a placeholder...
	return currentTargetWaypoints - m_tankBase.getPosition();
}

////////////////////////////////////////////////////////////
sf::Vector2f TankAi::collisionAvoidance()
{
	auto headingRadians = thor::toRadian(m_rotation);
	sf::Vector2f headingVector(std::cos(headingRadians) * MAX_SEE_AHEAD, std::sin(headingRadians) * MAX_SEE_AHEAD);
	m_ahead = m_tankBase.getPosition() + headingVector;
	m_halfAhead = m_tankBase.getPosition() + (headingVector * 0.5f);
	const sf::CircleShape mostThreatening = findMostThreateningObstacle();
	sf::Vector2f avoidance(0, 0);
	if (mostThreatening.getRadius() != 0.0)
	{		
		if (MathUtility::distance(m_ahead, mostThreatening.getPosition()) >= mostThreatening.getRadius()* 0.99 && 
			MathUtility::distance(m_ahead, mostThreatening.getPosition()) <= mostThreatening.getRadius() * 1.01)
		{
			avoidance *= 0.0f;
		}
		else
		{
			avoidance.x = m_ahead.x - mostThreatening.getPosition().x;
			avoidance.y = m_ahead.y - mostThreatening.getPosition().y;
			avoidance = thor::unitVector(avoidance);
			avoidance *= MAX_AVOID_FORCE;
		}
	}
	else
	{
		avoidance *= 0.0f;
	}
	return avoidance;
}

////////////////////////////////////////////////////////////
const sf::CircleShape TankAi::findMostThreateningObstacle()
{
	// The initialisation of mostThreatening is just a placeholder...
	// sf::CircleShape mostThreatening = m_obstacles.at(0);
	sf::CircleShape mostThreatening;
	mostThreatening.setRadius(0);

	for (int i = 0; i < m_obstacles.size() ; i++)
	{
		sf::CircleShape obstacle = m_obstacles[i];
		bool collision = (MathUtility::lineIntersectsCircle(m_ahead, m_halfAhead, obstacle));

		if (collision && (mostThreatening.getRadius() != 0 || 
			MathUtility::distance(m_tankBase.getPosition(), obstacle.getPosition()) < MathUtility::distance(m_tankBase.getPosition() , mostThreatening.getPosition())))
		{
			mostThreatening = obstacle;
		}
	}
	return mostThreatening;
}

void TankAi::PatrolMap()
{

	int result = MathUtility::distance(m_tankBase.getPosition(), m_wayPoints[m_nextWayPoint]);

	if (result < 10)
	{
		m_nextWayPoint = (m_nextWayPoint + 1) % m_wayPoints.size();
	}
}

void TankAi::visionConeBehavior(Tank const& playerTank)
{
	sf::Vector2f AITankPos = m_turret.getPosition();
	sf::Vector2f playerTankPos = playerTank.getPosition();

	m_visionConeLeft = AITankPos;
	m_visionConeRight = AITankPos;

	m_arrowLeft.setStyle(thor::Arrow::Style::Line);
	m_arrowRight.setStyle(thor::Arrow::Style::Line);
	
	m_arrowLeft.setPosition(m_visionConeLeft);
	m_arrowRight.setPosition(m_visionConeRight);

	sf::Vector2f arrowLeftDirection;
	sf::Vector2f arrowRightDirection;

	if (m_aiBehaviour == AiBehaviour::PATROL_MAP)
	{
		arrowLeftDirection = m_patrolConeLength * thor::rotatedVector(m_visionConeDir, m_turret.getRotation() - m_patrolConeAngle);
		arrowRightDirection = m_patrolConeLength * thor::rotatedVector(m_visionConeDir, m_turret.getRotation() + m_patrolConeAngle);
		m_arrowLeft.setColor(sf::Color::Green);
		m_arrowRight.setColor(sf::Color::Green);
	}
	else if(m_aiBehaviour == AiBehaviour::ATTACK_PLAYER)
	{
		arrowLeftDirection = m_attackConeLength * thor::rotatedVector(m_visionConeDir, m_turret.getRotation() - m_attackConeAngle);
		arrowRightDirection = m_attackConeLength * thor::rotatedVector(m_visionConeDir, m_turret.getRotation() + m_attackConeAngle);
		m_arrowLeft.setColor(sf::Color::Red);
		m_arrowRight.setColor(sf::Color::Red);

		/*if (MathUtility::distance(playerTankPos, AITankPos) >= m_attackConeLength)
		{
			arrowLeftDirection = m_attackConeLength * thor::rotatedVector(m_visionConeDir, m_turret.getRotation() - m_attackConeAngle);
			arrowRightDirection = m_attackConeLength * thor::rotatedVector(m_visionConeDir, m_turret.getRotation() + m_attackConeAngle);
			m_arrowLeft.setColor(sf::Color::Red);
			m_arrowRight.setColor(sf::Color::Red);
		}
		else
		{
			arrowLeftDirection = m_playerHalfWayLength * thor::rotatedVector(m_visionConeDir, m_turret.getRotation() - m_playerHalfWayAngle);
			arrowRightDirection = m_playerHalfWayLength * thor::rotatedVector(m_visionConeDir, m_turret.getRotation() + m_playerHalfWayAngle);
			m_arrowLeft.setColor(sf::Color::Blue);
			m_arrowRight.setColor(sf::Color::Blue);

		}*/
		
	}

	m_arrowLeft.setDirection(arrowLeftDirection);
	m_arrowRight.setDirection(arrowRightDirection);

	arrowLeftPoints = AITankPos + arrowLeftDirection;
	arrowRightPoints = AITankPos + arrowRightDirection;

}

void TankAi::isPlayerInCone(sf::Vector2f turretPos, sf::Vector2f leftConePos, sf::Vector2f rightConePos, Tank const& playerTank)
{
	sf::Vector2f playerPos = playerTank.getPosition();

	sf::Vector2f v1 = { leftConePos - turretPos };
	sf::Vector2f v2 = { turretPos - rightConePos };
	sf::Vector2f v3 = { rightConePos - leftConePos };

	sf::Vector2f v4 = { playerPos - turretPos };
	sf::Vector2f v5 = { playerPos - rightConePos };
	sf::Vector2f v6 = { playerPos - leftConePos };

	double result1 = thor::dotProduct(v1, v4);
	double result2 = thor::dotProduct(v2, v5);
	double result3 = thor::dotProduct(v3, v6);

	if (result1 >= 0 && result2 >= 0 && result3 >= 0)
	{
		m_aiBehaviour = AiBehaviour::ATTACK_PLAYER;
	}
	else
	{
		m_aiBehaviour = AiBehaviour::PATROL_MAP;
	}
}

void TankAi::visionConeRotation()
{
	if (m_aiBehaviour == AiBehaviour::PATROL_MAP)
	{
		m_arrowLeft.setRotation(m_arrowLeft.getRotation() + 0.8);
		m_arrowRight.setRotation(m_arrowLeft.getRotation() + 0.8);
	}
	else if (m_aiBehaviour == AiBehaviour::ATTACK_PLAYER)
	{
		m_arrowLeft.setRotation(0);
		m_arrowRight.setRotation(0);
	}
}

bool TankAi::collidesWithPlayer(Tank const& playerTank) const
{
	// Checks if the AI tank has collided with the player tank.
	if (CollisionDetector::collision(m_turret, playerTank.getTurret()) ||
		CollisionDetector::collision(m_tankBase, playerTank.getBase()))
	{
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////
void TankAi::initSprites()
{
	// Initialise the tank base
	m_tankBase.setTexture(m_texture);
	sf::IntRect baseRect(103, 43, 79, 43);
	m_tankBase.setTextureRect(baseRect);
	m_tankBase.setScale(0.7, 0.7);
	m_tankBase.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);

	// Initialise the turret
	m_turret.setTexture(m_texture);
	sf::IntRect turretRect(122, 1, 83, 31);
	m_turret.setTextureRect(turretRect);
	m_turret.setScale(0.7, 0.7);
	m_turret.setOrigin(turretRect.width / 3.0, turretRect.height / 2.0);
}


////////////////////////////////////////////////////////////
void TankAi::updateMovement(double dt)
{
	double speed = thor::length(m_velocity);
	sf::Vector2f newPos(m_tankBase.getPosition().x + std::cos(MathUtility::DEG_TO_RAD  * m_rotation) * speed * (dt / 1000),
						m_tankBase.getPosition().y + std::sin(MathUtility::DEG_TO_RAD  * m_rotation) * speed * (dt / 1000));
	m_tankBase.setPosition(newPos.x, newPos.y);
	m_tankBase.setRotation(m_rotation);
	m_turret.setPosition(m_tankBase.getPosition());
	m_turret.setRotation(m_rotation);
}