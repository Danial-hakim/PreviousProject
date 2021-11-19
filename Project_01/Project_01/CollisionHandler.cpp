#include "CollisionHandler.h"

bool CollisionHandler::player_Boundary(Grid& grid, Player& player)
{
	int playerRow = round((player.getPos().x + grid.getCellOrigin().x) / grid.cellWidth); 
	int playerCol = round((player.getPos().y + grid.getCellOrigin().y) / grid.cellHeight);

	std::vector<Cell> cell = grid.getCell();

	int maxCellnum = ScreenSize::ROWS * ScreenSize::COLUMNS;

	int playerCell = ((playerRow - 1)  * ScreenSize::COLUMNS) + (playerCol - 1);

	for (int i = 0; i < maxCellnum; i++)
	{
		if (cell.at(i).id() == playerCell) //((playerRow - 1) * ScreenSize::ROWS + (playerCol - 1)))
		{
			if (cell.at(i).getPassable() == false)
			{
				std::cout << "Collision" << std::endl;
				std::cout << playerCell << std::endl;
				std::cout << i << std::endl;
				std::cout << "=========" << std::endl;
				return true;
				break;
			}
		}
	}

	return false;
}
