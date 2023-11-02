#include "removeEdgeAdjacentBlocks.h"

void removeEdgeAdjacentBlocks(std::vector<std::vector<int>>& grid) {
    //meret lekerdezese
    int numRows = grid.size();
    int numCols = grid[0].size();

    // felso es also folyosok kinullazasa
    for (int col = 0; col < numCols; col++) { //!< A felsõés alsó sorokat kinullázzuk tehát egy pálya határt szabunk a játékosnak
        grid[1][col] = 0;                //!< A felsõ folyosó kinullázása
        grid[numRows - 2][col] = 0;     //!< Az also folyosó kinullázása
    }

    // bal es jobb oldali folyosok kinullazasa
    for (int row = 1; row < numRows - 1; row++) { //!< A jobb és bal oldali folyosók nullázása pálya határ meghúzása miatt
        grid[row][1] = 0;                //!< A bal folyosó nullázása
        grid[row][numCols - 2] = 0;     //!< A jobb folyosó nullázása
    }
}
