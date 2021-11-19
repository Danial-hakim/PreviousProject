#pragma once
// Items
#include "Scanner.h"
#include "NoiseMaker.h"
#include "Book.h"
#include "SmokeBomb.h"
#include "Grid.h"


class ItemStorage
{
protected:
	std::vector<Item*> storedItems;
	std::vector<std::vector<Item*>::iterator> toBeDeleted;

	std::vector<Item*>::iterator findItemInStorage(Item* checkedItemAgainst, bool checkIfInInventory);
	void deleteItem(Item* itemToDelete, std::vector<Item*>::iterator pointInInventory);

public:

	ItemStorage();

	void update();
	virtual void render(sf::RenderWindow& t_window);
	void addItem(Item* newItem);
	Item* getItem(ItemType type);

};