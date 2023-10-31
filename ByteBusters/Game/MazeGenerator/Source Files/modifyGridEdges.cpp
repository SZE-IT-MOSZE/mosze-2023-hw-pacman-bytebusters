#include "modifyGridEdges.h"

void modifyGridEdges(std::vector<std::vector<int>>& grid) {
    //!< A méret lekérdezése
    int numRows = grid.size();
    int numCols = grid[0].size();
    //! Az also és felsõsorok kinullázása
    for (int col = 0; col < numCols; col++) {
        grid[0][col] = 1;                //!< A felsõ sor
        grid[numRows - 1][col] = 1;     //!< Az alsó sor
    }
    //!< A bal es jobb oldal kinullázása
    for (int row = 1; row < numRows - 1; row++) {
        grid[row][0] = 1;                //!< A bal oldal
        grid[row][numCols - 1] = 1;     //!< A jobb oldal
    }
}
