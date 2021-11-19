#pragma once

// Other
#include "ItemStorage.h"
#include "ScreenSize.h"
#include <vector>
#include <array>
#include <iterator>
#include "SoundManager.h"

class Inventory : public ItemStorage
{
private:

	// consts for the layout of the items when inventory open
	const static int ITEM_AMOUNT = 4;
	const sf::Vector2f START_DIST = sf::Vector2f(ScreenSize::s_width / 5.0f, ScreenSize::s_height / 2.0f);
	const sf::Vector2f SELECTION_START_DIST = START_DIST;
	const int DIST_BETWEEN_ITEMS = (ScreenSize::s_width - START_DIST.x) / 4.0f;
	const sf::Vector2f ITEM_SIZE = sf::Vector2f(160, 140);

	// Design
	sf::RectangleShape background;
	sf::RectangleShape selection;
	sf::RectangleShape equippedItemHighlight;
	sf::Text m_itemCount[ITEM_AMOUNT];
	sf::Font* m_font = nullptr;

	ScannerObserver* mapItemsObserver;

	bool inventoryOpen;
	Item* equippedItem;

	bool notEnoughItems(std::array<int, 4> items, int t_col);

	void moveSelectionLeft();
	void moveSelectionRight();
	void pickUpItem(sf::Vector2f playerPos);

	void renderItems(sf::RenderWindow& t_window);
	std::array<int, 4> countItems();

public:
	Inventory(ScannerObserver* t_observer);
	void getFont(sf::Font* t_font);

	void handleKeyInventoryInput(sf::Event& event, sf::Vector2f playerPos, float t_angle);
	bool inventoryIsOpen();
	void equipItem();
	void useItem(sf::Vector2f playerPos, float t_angle);

	void render(sf::RenderWindow& t_window) override;
};

