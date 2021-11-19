#pragma once
#include "Item.h"
class ThrowableItem : public Item
{
private:
    void throwItem(float t_angle);
    float angleCalculation(sf::Vector2f t_playerDirection);
    sf::Vector2f playerPos;


protected:

    const int THROW_DISTANCE = 200; 

public:

    ThrowableItem(ItemType t_type);
    ThrowableItem(ItemType t_type, sf::Vector2f t_position);
    void useItem(sf::Vector2f t_playerPos, float t_angle);

    bool updateThrow();
};

