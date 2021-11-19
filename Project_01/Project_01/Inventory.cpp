#include "Inventory.h"

bool Inventory::notEnoughItems(std::array<int, 4> items, int t_col)
{
	return items[t_col] <= 0;
}

void Inventory::moveSelectionLeft()
{
	if (selection.getPosition().x - DIST_BETWEEN_ITEMS <= 0)
	{
		selection.setPosition(SELECTION_START_DIST.x + (DIST_BETWEEN_ITEMS * 3), SELECTION_START_DIST.y);
	}

	else
	{
		selection.setPosition(selection.getPosition().x - DIST_BETWEEN_ITEMS,
			SELECTION_START_DIST.y);
	}

	SoundManager::causeSound(NoiseTypes::MoveSelection);
}

void Inventory::moveSelectionRight()
{
	if (selection.getPosition().x + selection.getSize().x + DIST_BETWEEN_ITEMS >= ScreenSize::s_width)
	{
		selection.setPosition(SELECTION_START_DIST);
	}

	else
	{
		selection.setPosition(selection.getPosition().x + DIST_BETWEEN_ITEMS,
			SELECTION_START_DIST.y);
	}
	SoundManager::causeSound(NoiseTypes::MoveSelection);
}

void Inventory::pickUpItem(sf::Vector2f playerPos)
{
	Item* pickedUpItem = mapItemsObserver->pickUpItem(playerPos);

	if (pickedUpItem != nullptr)
	{
		pickedUpItem->pickUpItem();
		storedItems.push_back(pickedUpItem);
	}

}

Inventory::Inventory(ScannerObserver* t_observer) : mapItemsObserver(t_observer)
{
	inventoryOpen = false;
	equippedItem = nullptr;

	background.setFillColor(sf::Color(0,0,0,150));
	background.setSize(sf::Vector2f(ScreenSize::s_width, ScreenSize::s_height));

	addItem(new NoiseMaker());
	addItem(new NoiseMaker());
	addItem(new NoiseMaker());

	addItem(new Scanner(t_observer));
	addItem(new Book("A up"));
	addItem(new Book("B right"));

	selection.setFillColor(sf::Color(0, 0, 0, 0));
	selection.setOutlineColor(sf::Color::Green);
	selection.setOutlineThickness(20);	
	selection.setSize(sf::Vector2f(220,220));
	selection.setPosition(SELECTION_START_DIST);
	selection.setOrigin(sf::Vector2f(selection.getSize().x / 2.0f, selection.getSize().y / 2.0f));

	equippedItemHighlight.setFillColor(sf::Color(255, 255, 255, 100));
	equippedItemHighlight.setSize(sf::Vector2f(220, 220));
	equippedItemHighlight.setPosition(SELECTION_START_DIST);
	equippedItemHighlight.setOrigin(sf::Vector2f(selection.getSize().x / 2.0f, selection.getSize().y / 2.0f));

}

void Inventory::getFont(sf::Font* t_font)
{
	m_font = t_font;

	for (int i = 0; i < ITEM_AMOUNT; i++)
	{
		m_itemCount[i].setFont(*m_font);
		m_itemCount[i].setString(std::to_string(i));
		m_itemCount[i].setOutlineColor(sf::Color(107, 107, 107));
		m_itemCount[i].setOutlineThickness(5);
		m_itemCount[i].setCharacterSize(45);
		m_itemCount[i].setPosition(sf::Vector2f(START_DIST.x + ITEM_SIZE.x / 3.0f + (i * DIST_BETWEEN_ITEMS), START_DIST.y + ITEM_SIZE.y / 4.0f));
	}
}

void Inventory::handleKeyInventoryInput(sf::Event& event, sf::Vector2f playerPos, float t_angle)
{
	Scanner* scanner = dynamic_cast<Scanner*>(getItem(ItemType::SCANNER));

	if (event.type != sf::Event::MouseButtonPressed)
	{
		sf::Keyboard::Key key = event.key.code;

		if (sf::Event::KeyPressed == event.type)
		{
			if (scanner == nullptr || !scanner->isScannerOn())
			{
				if (key == sf::Keyboard::I)
				{
					inventoryOpen = !inventoryOpen;
					selection.setPosition(SELECTION_START_DIST);
				}

				if (inventoryOpen)
				{
					if (key == sf::Keyboard::A || key == sf::Keyboard::Left)
					{
						moveSelectionLeft();
					}

					else if (key == sf::Keyboard::D || key == sf::Keyboard::Right)
					{
						moveSelectionRight();
					}

					else if (key == sf::Keyboard::E)
					{
						equipItem();
						selection.setOutlineColor(sf::Color::Yellow);
					}
				}

				else
				{
					if (key == sf::Keyboard::E)
					{
						useItem(playerPos,t_angle);
					}
				}
			}

			else
			{
				if (key == sf::Keyboard::E)
				{
					useItem(playerPos, t_angle);
				}
			}
		}

		else if (key == sf::Keyboard::E && inventoryOpen)
		{
			selection.setOutlineColor(sf::Color::Green);
		}
	}

	else
	{
		pickUpItem(playerPos);
	}
}

bool Inventory::inventoryIsOpen()
{
	return inventoryOpen;
}


void Inventory::equipItem()
{
	float selectionPos = std::roundf(selection.getPosition().x);

	for (Item* selectedItem : storedItems)
	{
		bool in = selectedItem->inInventory();
		float i = std::roundf(selectedItem->getBody().getPosition().x);

		if (selectionPos == i
			&& selectedItem->inInventory())
		{
			equippedItem = selectedItem;
			break;
		}
	}
	
	if (equippedItem != nullptr)
	{
		std::cout << "equipped " << equippedItem->getItemType() << std::endl;
	}

	SoundManager::causeSound(NoiseTypes::Select);
}

void Inventory::useItem(sf::Vector2f playerPos, float t_angle)
{
	if (equippedItem != nullptr)
	{
		if (equippedItem->getItemType() != ItemType::SCANNER)
		{
			auto iter = findItemInStorage(equippedItem, true);

			try
			{
				ThrowableItem* thrownItem = static_cast<ThrowableItem*>(equippedItem);

				thrownItem->useItem(playerPos, t_angle);
			}

			catch (int e)
			{

			}

			equippedItem->useItem();

			if (equippedItem->getItemType() == ItemType::BOOK)
			{
				deleteItem(equippedItem, iter);
			}

			equippedItem = nullptr;
		}

		else
		{
			equippedItem->useItem();
		}

	}
}

void Inventory::render(sf::RenderWindow& t_window)
{
	for (Item* t_item : storedItems)
	{
		if (!t_item->inInventory())
		{
			t_item->renderOnGrid(t_window);
		}
	}

	getItem(ItemType::SCANNER)->renderOnGrid(t_window);

	if (inventoryOpen)
	{
		if (inventoryOpen)
		{
			t_window.draw(background);

			renderItems(t_window);

			t_window.draw(selection);
		}
	}
}

void Inventory::renderItems(sf::RenderWindow& t_window)
{
	if (!storedItems.empty())
	{
		std::array<int, 4> items = countItems();
		int itemPlacement = 0;
		Item* drawnItem;
		sf::Vector2f itemPoint;

		for (int col = 0; col < ITEM_AMOUNT; col++)
		{
			if (notEnoughItems(items, col))
			{
				continue;
			}

			itemPoint = sf::Vector2f(START_DIST.x + (itemPlacement * DIST_BETWEEN_ITEMS), START_DIST.y);
			drawnItem = getItem(static_cast<ItemType>(col + 1));
			drawnItem->moveBody(itemPoint);

			m_itemCount[itemPlacement].setString(std::to_string(items[col]));

			drawnItem->renderInInventory(t_window);

			if (equippedItem != nullptr && drawnItem->getItemType() == equippedItem->getItemType())
			{
				equippedItemHighlight.setPosition(drawnItem->getBody().getPosition());
				t_window.draw(equippedItemHighlight);
			}

			t_window.draw(m_itemCount[itemPlacement]);

			itemPlacement++;

		}

	}
}

std::array<int, 4> Inventory::countItems()
{
	std::array<int, 4> itemAmounts { 0,0,0,0 };

	for (Item* indexItem : storedItems)
	{
		if (indexItem->inInventory())
		{
			itemAmounts[static_cast<int>(indexItem->getItemType()) - 1]++;
		}
	}

	return itemAmounts;
}
