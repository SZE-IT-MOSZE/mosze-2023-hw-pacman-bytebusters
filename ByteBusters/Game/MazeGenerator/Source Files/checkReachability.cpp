#include "checkReachability.h"
#include <vector>


/**
 * @file checkReachability.h
 * @brief A checkReachability függvény impementacioja.
 *
 * Implementalja a checkReachability függvényt, amely ellenőrzi, hogy a grid minden nullával jelölt
 * cellája elérhető-e a rács széleiről.
 */

 /**
  * @brief Függvény prototípusa egy rács elérhetőségének ellenőrzésére.
  *
  * Ez a függvény ellenőrzi, hogy a grif minden nullával jelölt cellája elérhető-e a rács széleiről.
  * A függvény DEEP FIRST SEARCH (DFS) alkalmaz a grid bejárására, megállapítva, hogy minden
  * nullás értékű cella elérhető-e anélkül, hogy át kellene menni egy nem-nullás cellán.
  *
  * @param grid Egy konstans referencia egy 2D egész számokból álló vektorra, amely maga a grid.
  * @return Igaz, ha minden nullával jelölt cella elérhető a szélekről, egyébként meg hamis.
  */

//!< depth-first search
void dfs(const std::vector<std::vector<int>>& grid, int row, int col, std::vector<std::vector<bool>>& visited) {
    //!< A méret lekérése
    int numRows = grid.size();
    int numCols = grid[0].size();

    //!< A lehetséges lépések halmaza egy adott koordinátaról
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    visited[row][col] = true;

    //!< Egy loop, ahozz hogy megnézzük a környékbeli lépéseket
    for (int d = 0; d < 4; d++) {
        int newRow = row + dx[d];
        int newCol = col + dy[d];

        if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && grid[newRow][newCol] == 0 && !visited[newRow][newCol]) {
            dfs(grid, newRow, newCol, visited);
        }
    }
}

bool checkReachability(const std::vector<std::vector<int>>& grid) {
    //!< A meret lekérése
    int numRows = grid.size();
    int numCols = grid[0].size();

    // latogatott cellak tarolasa
    std::vector<std::vector<bool>> visited(numRows, std::vector<bool>(numCols, false));

    //!< A deep first search kezdete a szélek felöl
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if ((row == 0 || row == numRows - 1 || col == 0 || col == numCols - 1) && grid[row][col] == 0 && !visited[row][col]) {
                dfs(grid, row, col, visited);
            }
        }
    }

    //!< Azt nézzuk meg minden 0 belekerult-e a visited tömbbe
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if (grid[row][col] == 0 && !visited[row][col]) {
                return false;
            }
        }
    }

    return true;
}
