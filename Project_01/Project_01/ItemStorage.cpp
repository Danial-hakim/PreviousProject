#include "ItemStorage.h"

std::vector<Item*>::iterator ItemStorage::findItemInStorage(Item* checkedItemAgainst, bool checkIfInInventory)
{
	bool inventoryCheck = true;

	if (checkIfInInventory)
	{
		inventoryCheck = checkedItemAgainst->inInventory();
	}

	auto iter = storedItems.begin();

	for (Item* item : storedItems)
	{

		if (item == checkedItemAgainst && inventoryCheck)
		{
			break;
		}

		iter++;
	}

	return iter;
}

void ItemStorage::deleteItem(Item* itemToDelete, std::vector<Item*>::iterator pointInInventory)
{
	if (itemToDelete != nullptr)
	{
		delete itemToDelete;
		storedItems.erase(pointInInventory);
		itemToDelete = nullptr;
	}
}

ItemStorage::ItemStorage()
{

}

void ItemStorage::update()
{
	for (Item* indexItem : storedItems)
	{
		indexItem->update();

		if (indexItem->shouldBeDeleted())
		{
			auto iter = findItemInStorage(indexItem, false);
			deleteItem(indexItem, iter);
		}
	}
}

void ItemStorage::render(sf::RenderWindow& t_window)
{
	for (Item* indexItem : storedItems)
	{
		indexItem->renderOnGrid(t_window);
	}
}

void ItemStorage::addItem(Item* newItem)
{
	storedItems.push_back(newItem);
}

Item* ItemStorage::getItem(ItemType type)
{
	Item* pointer = nullptr;

	for (Item* indexItem : storedItems)
	{
		if (indexItem->getItemType() == type && indexItem->inInventory())
		{
			pointer = indexItem;
		}
	}

	return pointer;
}
