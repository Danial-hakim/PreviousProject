#include "MapItems.h"

sf::Vector2f MapItems::getActualPosition(int t_row, int t_col)
{
	return sf::Vector2f((t_row * gridRef->cellWidth) + gridRef->cellWidth / 2.0f,
		(t_col * gridRef->cellHeight) + gridRef->cellHeight / 2.0f);
}

MapItems::MapItems(Alien* t_alien, Grid* t_grid)
	: alien_ref(t_alien), gridRef(t_grid)
{

	//addItem(new NoiseMaker(getActualPosition(2,4)));
	addItem(new SmokeBomb(getActualPosition(8, 9), gridRef));
	addItem(new SmokeBomb(getActualPosition(1, 1), gridRef));
	addItem(new SmokeBomb(getActualPosition(2, 2), gridRef));
	addItem(new SmokeBomb(getActualPosition(3, 3), gridRef));
	 

	scannerIcon.setFillColor(sf::Color::Yellow);
	scannerIcon.setRadius((ScreenSize::s_height / ScreenSize::COLUMNS) / 2.0f);
	scannerIcon.setOrigin(scannerIcon.getRadius(), scannerIcon.getRadius());
}

void MapItems::drawItemsForScanner(sf::RenderWindow& t_window)
{
	sf::Vector2f temp;

	for (Item* indexItem : storedItems)
	{
		temp = indexItem->getBody().getPosition();
		scannerIcon.setPosition(temp);
		t_window.draw(scannerIcon);
	}

	scannerIcon.setPosition(alien_ref->getPos());
	t_window.draw(scannerIcon);
}

std::vector<int> MapItems::getItemIDs()
{
	std::vector<int> itemIDs;
	int id;

	for (Item* item : storedItems)
	{
		id = gridRef->getCellID(item->getMapPos());

		itemIDs.push_back(id);
	}

	return itemIDs;
}

Item* MapItems::pickUpItem(sf::Vector2f currentPos)
{
	std::vector<int> itemIDs = getItemIDs();
	int playerID = gridRef->getCellID(currentPos);

	for (Item* currentItem : storedItems)
	{
		if (gridRef->cellsNearEachother(playerID, gridRef->getCellID(currentItem->getMapPos())))
		{
			storedItems.erase(std::remove(storedItems.begin(),
				storedItems.end(), currentItem), storedItems.end());

			return currentItem;
		}
	}
	return nullptr;
}