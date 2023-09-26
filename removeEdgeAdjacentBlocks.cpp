#include "removeEdgeAdjacentBlocks.h"

void removeEdgeAdjacentBlocks(std::vector<std::vector<int>>& grid) {
    //meret lekerdezese
    int numRows = grid.size();
    int numCols = grid[0].size();

    // felso es also folyosok kinullazasa
    for (int col = 0; col < numCols; col++) {
        grid[1][col] = 0;                // felso
        grid[numRows - 2][col] = 0;     // also
    }

    // bal es jobb oldali folyosok kinullazasa
    for (int row = 1; row < numRows - 1; row++) {
        grid[row][1] = 0;                // bal
        grid[row][numCols - 2] = 0;     // jobb
    }
}
