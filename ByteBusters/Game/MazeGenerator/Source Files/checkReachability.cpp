#include "checkReachability.h"
#include <vector>

//!< depth-first search
void dfs(const std::vector<std::vector<int>>& grid, int row, int col, std::vector<std::vector<bool>>& visited) {
    //!< A m�ret lek�r�se
    int numRows = grid.size();
    int numCols = grid[0].size();

    //!< A lehets�ges l�p�sek halmaza egy adott koordin�tar�l
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    visited[row][col] = true;

    //!< Egy loop, ahozz hogy megn�zz�k a k�rny�kbeli l�p�seket
    for (int d = 0; d < 4; d++) {
        int newRow = row + dx[d];
        int newCol = col + dy[d];

        if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && grid[newRow][newCol] == 0 && !visited[newRow][newCol]) {
            dfs(grid, newRow, newCol, visited);
        }
    }
}

bool checkReachability(const std::vector<std::vector<int>>& grid) {
    //!< A meret lek�r�se
    int numRows = grid.size();
    int numCols = grid[0].size();

    // latogatott cellak tarolasa
    std::vector<std::vector<bool>> visited(numRows, std::vector<bool>(numCols, false));

    //!< A deep first search kezdete a s�lek fel�l
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if ((row == 0 || row == numRows - 1 || col == 0 || col == numCols - 1) && grid[row][col] == 0 && !visited[row][col]) {
                dfs(grid, row, col, visited);
            }
        }
    }

    //!< Azt n�zzuk meg minden 0 belekerult-e a visited t�mbbe
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if (grid[row][col] == 0 && !visited[row][col]) {
                return false;
            }
        }
    }

    return true;
}
