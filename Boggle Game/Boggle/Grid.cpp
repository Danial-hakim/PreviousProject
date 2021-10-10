#include "Grid.h"

void Grid::randomiseLetters()
{
    for (int i = 0; i < 16; i++)
    {
        rand[i] = std::rand() % 6;
        chosenLetters[i] = DIE[i][rand[i]];
    }
}

int Grid::passCellNumber(int t_arrayCell)
{
    return rand[t_arrayCell];
}

std::string Grid::passConstantValues(int t_array, int t_arrayCell)
{
    return DIE[t_array][t_arrayCell];
}

std::string Grid::passRandomisedValues(int t_arrayCell)
{
    return chosenLetters[t_arrayCell];
}

