#pragma once
#include "ItemStorage.h"
#include "ScannerObserver.h"
#include "Alien.h"

class MapItems : public ItemStorage, public ScannerObserver
{
private:
	sf::CircleShape scannerIcon;
	sf::Vector2f getActualPosition(int t_row, int t_col);
	Alien* alien_ref;
	Grid* gridRef;
	std::vector<int> getItemIDs();

public:
	MapItems(Alien* t_alien, Grid *t_grid);
	void drawItemsForScanner(sf::RenderWindow& t_window);
	Item* pickUpItem(sf::Vector2f currentPos);
};

