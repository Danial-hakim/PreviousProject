#include "ThrowableItem.h"

void ThrowableItem::throwItem(float t_angle)
{
	onMap = true;
	
	//float angle = angleCalculation(t_playerDirection);
	mapPosition = playerPos;
	m_itemBody.setPosition(playerPos);
	m_itemBody.setRotation(t_angle);
	speed = 2;
	velocity = sf::Vector2f(cosf(t_angle * M_PI / 180.0) * speed,
		sinf(t_angle * M_PI / 180.0) * speed);
}

float ThrowableItem::angleCalculation(sf::Vector2f t_playerDirection)
{
	sf::Vector2f vectorB = sf::Vector2f(1, 0);
	sf::Vector2f vectorA = t_playerDirection;
	float angle{ 0.0f };

	if (t_playerDirection.x != 0 || t_playerDirection.y != 0)
	{
		float dotProduct{ 0.0f };
		float aLength{ 0.0f };
		float bLength{ 0.0f };
		const float RAD_TO_DEG{ 180 / M_PI };

		// Assigning values using other functions
		dotProduct = (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y);	// Calculates dot product

		aLength = sqrt((vectorA.x * vectorA.x) + (vectorA.y * vectorA.y));
		bLength = sqrt((vectorB.x * vectorB.x) + (vectorB.y * vectorB.y));


		// calculating the angle
		angle = dotProduct / (aLength * bLength); // gets the sum that appears after the cos
		angle = acos(angle);
	}

	return angle; // returns the calculated angle

}

ThrowableItem::ThrowableItem(ItemType t_type, sf::Vector2f t_position)
	: Item(t_type, t_position)
{
}

void ThrowableItem::useItem(sf::Vector2f t_playerPos, float t_angle)
{
	playerPos = t_playerPos;
	throwItem(t_angle);
}

ThrowableItem::ThrowableItem(ItemType t_type)
	: Item(t_type)

{

}

bool ThrowableItem::updateThrow()
{
	if (onMap && pickedUp)
	{
		mapPosition += velocity;

		sf::Vector2f s = mapPosition - playerPos;
		float l = std::sqrt(s.x * s.x + s.y * s.y);

		return l > THROW_DISTANCE;
	}

	return false;
}
