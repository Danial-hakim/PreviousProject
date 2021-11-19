#include "Grid.h"

Grid::Grid()
{
	m_cells.resize(ScreenSize::ROWS * ScreenSize::COLUMNS);

	for (int i = 0; i < ScreenSize::ROWS * ScreenSize::COLUMNS; i++)
	{
		m_cells.at(i).setId(i);
	}

	for (int row = 0; row < ScreenSize::ROWS; row++)
	{
		for (int col = 0; col < ScreenSize::COLUMNS; col++)
		{
			int index = col * ScreenSize::ROWS + row;
			float rowOffset = row * cellHeight;
			float colOffset = col * cellWidth;

			m_cells.at(index).setCentre(sf::Vector2f(rowOffset + cellWidth / 2, colOffset + cellHeight / 2));
			neighbours(row, col);
		}
	}
}

void Grid::init()
{
	for (int i = 0; i < ScreenSize::ROWS; i++)
	{
		for (int j = 0; j < ScreenSize::COLUMNS; j++)
		{
			grid[i][j].setSize(sf::Vector2f(cellWidth, cellHeight));

			grid[i][j].setPosition(i * cellWidth, j * cellHeight);

			grid[i][j].setOutlineThickness(1);

			grid[i][j].setOutlineColor(sf::Color::Blue);

			grid[i][j].setFillColor(sf::Color::Transparent);
		}
	}

	makeWallsImpassable();
	hardCodeLevelOne();
}

void Grid::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < ScreenSize::ROWS; i++)
	{
		for (int j = 0; j < ScreenSize::COLUMNS; j++)
		{
			window.draw(grid[i][j]);
		}
	}

	//debugMode(window);
}

void Grid::neighbours(int t_row, int t_col)
{
	for (int direction = 0; direction < SURROUNDING_NEIGHBOURS; direction++)
	{
		int n_row = t_row + ((direction / 3) - 1); // neighbour row
		int n_col = t_col + ((direction % 3) - 1);

		if (n_row >= 0 && n_row < ScreenSize::ROWS && n_col >= 0 && n_col < ScreenSize::COLUMNS)
		{
			int neighbourIndex = n_row * ScreenSize::COLUMNS + n_col;
			int index = t_row * ScreenSize::COLUMNS + t_col;

			m_cells.at(index).addNeighbours(neighbourIndex);
		}
	}
}

void Grid::makeWallsImpassable()
{
	int cellID = 0;

	for (int i = 0; i < ScreenSize::ROWS; i++) 
	{
		cellID = i * ScreenSize::COLUMNS;
		m_cells.at(cellID).setPassable(false);
		grid[i][0].setFillColor(sf::Color::Green);
		/*std::cout << cellID << std::endl;
		std::cout << "=====" << std::endl;*/

		if (i == ScreenSize::ROWS - 1)
		{
			for (int j = 1; j < ScreenSize::COLUMNS; j++)
			{
				cellID = (i * ScreenSize::COLUMNS) + j; 
				m_cells.at(cellID).setPassable(false);
				grid[i][j].setFillColor(sf::Color::Green);

				/*std::cout << i << std::endl;
				std::cout << j << std::endl;*/
				/*std::cout << cellID << std::endl;
				std::cout << "=====" << std::endl;*/
			}
		}
	}

	for (int i = 1; i < ScreenSize::COLUMNS; i++)
	{
		cellID = i;
		m_cells.at(cellID).setPassable(false);
		grid[0][i].setFillColor(sf::Color::Green);

		if (i == ScreenSize::COLUMNS - 1)
		{
			for (int j = 1; j < ScreenSize::ROWS - 1; j++)
			{
				cellID = i * (j + 1) + j; 
				m_cells.at(cellID).setPassable(false);
				grid[j][i].setFillColor(sf::Color::Green);

				/*std::cout << cellID << std::endl;
				std::cout << "=====" << std::endl;*/
			}
		}
	}
}

void Grid::refreshImpassableCells()
{
	int cellID = 0;

	for (int i = 0; i < ScreenSize::ROWS; i++)
	{
		for (int j = 0; j < ScreenSize::COLUMNS; j++)
		{
			cellID = (i * ScreenSize::COLUMNS) + j;

			if (!m_cells[cellID].getPassable())
			{
				grid[i][j].setFillColor(sf::Color::Green);
			}

			else
			{
				grid[i][j].setFillColor(sf::Color::Transparent);
			}
		}
	}

}

void Grid::hardCodeLevelOne()
{
	int cellID = 0;

	for (int i = 10; i < ScreenSize::ROWS; i++) // horizontal 
	{
		for(int counter = 0; counter < 10; counter++)
		{
			if (counter % 5 == 0)
			{
				continue;
			}
			else
			{
				cellID = 12 + (counter * ScreenSize::COLUMNS);
				m_cells.at(cellID).setPassable(false);
				grid[counter][12].setFillColor(sf::Color::Green);
			}
		}
		for(int j = 5; j < 16 ; j += 10 )
		{ 
			if ((i + 1) % 5 == 0)
			{
				continue;
			}
			else
			{
				cellID = (i * ScreenSize::COLUMNS) + j;
				m_cells.at(cellID).setPassable(false);
				grid[i][j].setFillColor(sf::Color::Green);
			}
		}		
	}

	for (int i = 1; i < ScreenSize::COLUMNS; i++) // vertical 
	{
		for (int counter = 10; counter < ScreenSize::ROWS; counter += 8)
		{
			if ((i + 2) % 5 == 0)
			{
				continue;
			}
			else
			{
				cellID = (counter * ScreenSize::COLUMNS) + i;
				m_cells.at(cellID).setPassable(false);
				grid[counter][i].setFillColor(sf::Color::Green);
				//std::cout << cellID << std::endl;
			}
		}
	}

}

sf::Vector2f Grid::getCellOrigin()
{
	return sf::Vector2f(cellWidth/2, cellHeight/2);
}

std::vector<Cell> Grid::getCell()
{
	return m_cells;
}

void Grid::update(float dt)
{
	if (smokeBombActive)
	{
		for (std::pair<int, int>& i : smokeCells)
		{
			i.second--;

			if (i.second <= 0)
			{
				std::vector<int>* neighbours = &m_cells[i.first].neighbours();

				m_cells[i.first].setPassable(true);

				for (int i : *neighbours)
				{
					m_cells[i].setPassable(true);
				}

				smokeCells.erase(std::remove(smokeCells.begin(), smokeCells.end(), i), smokeCells.end());
				refreshImpassableCells();


				if (smokeCells.empty())
				{
					smokeBombActive = false;
				}
			}
		}
	}
}

void Grid::smokeBombReaction(sf::Vector2f t_smokeBombPosition)
{
	smokeBombActive = true;

	int id = getCellID(t_smokeBombPosition);

	std::vector<int>* neighbours = &m_cells[id].neighbours();

	m_cells[id].setPassable(false);

	for (int i : *neighbours)
	{
		m_cells[i].setPassable(false);
	}

	smokeCells.push_back(std::pair<int, int>(id, TIME_LEFT_FOR_SMOKE_TO_PASS));

	refreshImpassableCells();
}

bool Grid::cellsNearEachother(int A, int B)
{
	bool near = false;

	for (int c : m_cells[A].neighbours())
	{
		if (c == B)
		{
			near = true;
			break;
		}
	}

	return near;
}

int Grid::getCellID(sf::Vector2f t_position)
{
	return floor(t_position.x / cellWidth) * ScreenSize::COLUMNS + (floor(t_position.y / cellHeight));
}

void Grid::debugMode(sf::RenderWindow& window)
{
	if (!IDFont.loadFromFile("./Assets/Fonts/arial.ttf"))
	{
		std::cout << "Error with ID font" << std::endl;
	}

	IDText.setFont(IDFont);

	int col = 0;
	for (int i = 0; i < ScreenSize::ROWS; i++)
	{
		for (int j = 0; j < ScreenSize::COLUMNS; j++)
		{
			IDText.setString(std::to_string(col));
			IDText.setPosition(i * cellWidth, j * cellHeight);
			IDText.setFillColor(sf::Color::Red);
			window.draw(IDText);
			col++;
		}
	}


}
