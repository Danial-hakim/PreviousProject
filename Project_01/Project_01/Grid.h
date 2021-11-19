#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include "Cell.h"
#include "ScreenSize.h"

class Grid
{
public:

	Grid();

	void init();
	void draw(sf::RenderWindow& window);
	void neighbours(int t_row, int t_col);

	void makeWallsImpassable();
	void refreshImpassableCells();
	void hardCodeLevelOne();
	sf::Vector2f getCellOrigin();
	std::vector<Cell> getCell();

	void update(float dt);
	void smokeBombReaction(sf::Vector2f t_smokeBombPosition);

	bool cellsNearEachother(int A, int B);

	int getCellID(sf::Vector2f t_position);

	//Can delete later on
	void debugMode(sf::RenderWindow& window);

	const float cellWidth = ScreenSize::s_width / ScreenSize::ROWS;
	const float cellHeight = ScreenSize::s_height / ScreenSize::COLUMNS;

private:

	bool smokeBombActive = false;
	const int TIME_LEFT_FOR_SMOKE_TO_PASS = 300;
	std::vector<std::pair<int,int>> smokeCells;

	sf::RectangleShape grid[ScreenSize::ROWS][ScreenSize::COLUMNS];

	std::vector<Cell> m_cells;

	const int SURROUNDING_NEIGHBOURS{ 9 };

	sf::Font IDFont;
	sf::Text IDText;
};
