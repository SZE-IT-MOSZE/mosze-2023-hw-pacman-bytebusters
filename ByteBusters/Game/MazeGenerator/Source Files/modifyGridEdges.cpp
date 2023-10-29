#include "modifyGridEdges.h"

void modifyGridEdges(std::vector<std::vector<int>>& grid) {
    // meret lekerdezese
    int numRows = grid.size();
    int numCols = grid[0].size();
    // Also es felsosorok kinullasaza
    for (int col = 0; col < numCols; col++) {
        grid[0][col] = 1;                // felso
        grid[numRows - 1][col] = 1;     // also
    }
    // bal es jobb oldal kinullazasa
    for (int row = 1; row < numRows - 1; row++) {
        grid[row][0] = 1;                // bal
        grid[row][numCols - 1] = 1;     // jobb
    }
}
