#pragma once
#include <iostream>
#include "Grid.h"

class RenderGrid
{
private:
	//stores the passed in values from randomiseGrid
	  std::string randomLetter[16];
public:

	//draws the board to screen
	void  drawBoard(Grid t_grid);
};