#include "RenderGrid.h"

void RenderGrid::drawBoard(Grid t_grid)
{
    for (int i = 0; i < 16; i++)
    {
        randomLetter[i] = t_grid.passRandomisedValues(i);
    }
    std::cout << "                                               |  " << randomLetter[0] << "  |  " << randomLetter[1] << "  |  " << randomLetter[2] << "  |  " << randomLetter[3] << "  |  \n" << "                                               |  "
        << randomLetter[4] << "  |  " << randomLetter[5] << "  |  " << randomLetter[6] << "  |  " << randomLetter[7] << "  |  \n" << "                                               |  "
        << randomLetter[8] << "  |  " << randomLetter[9] << "  |  " << randomLetter[10] << "  |  " << randomLetter[11] << "  |  \n" << "                                               |  "
        << randomLetter[12] << "  |  " << randomLetter[13] << "  |  " << randomLetter[14] << "  |  " << randomLetter[15] << "  |  \n";
}
