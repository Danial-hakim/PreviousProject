#pragma once
#include "Item.h"
#include "SoundManager.h"
#include "Grid.h"
#include "ScannerObserver.h"

class Scanner : public Item
{
private:
	sf::RectangleShape background;
	bool screenOpen = false;

	ScannerObserver* observer;

	void initialise(ScannerObserver* t_observer);

public:
	Scanner(ScannerObserver* t_observer);
	Scanner(sf::Vector2f t_position, ScannerObserver* t_observer);

	void useItem();
	void update();
	void pickUpItem() override;

	void renderInInventory(sf::RenderWindow& t_window) override;
	void renderOnGrid(sf::RenderWindow& t_window) override;

	bool isScannerOn();

};

