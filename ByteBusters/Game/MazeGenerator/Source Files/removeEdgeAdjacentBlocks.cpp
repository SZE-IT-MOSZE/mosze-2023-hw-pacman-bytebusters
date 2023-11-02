#include "removeEdgeAdjacentBlocks.h"

void removeEdgeAdjacentBlocks(std::vector<std::vector<int>>& grid) {
    //meret lekerdezese
    int numRows = grid.size();
    int numCols = grid[0].size();

    // felso es also folyosok kinullazasa
    for (int col = 0; col < numCols; col++) { //!< A fels��s als� sorokat kinull�zzuk teh�t egy p�lya hat�rt szabunk a j�t�kosnak
        grid[1][col] = 0;                //!< A fels� folyos� kinull�z�sa
        grid[numRows - 2][col] = 0;     //!< Az also folyos� kinull�z�sa
    }

    // bal es jobb oldali folyosok kinullazasa
    for (int row = 1; row < numRows - 1; row++) { //!< A jobb �s bal oldali folyos�k null�z�sa p�lya hat�r megh�z�sa miatt
        grid[row][1] = 0;                //!< A bal folyos� null�z�sa
        grid[row][numCols - 2] = 0;     //!< A jobb folyos� null�z�sa
    }
}
