#include "checkReachability.h"
#include <vector>

//depth-first search
void dfs(const std::vector<std::vector<int>>& grid, int row, int col, std::vector<std::vector<bool>>& visited) {
    // meret lekerrese
    int numRows = grid.size();
    int numCols = grid[0].size();

    //lehetseges lepesek halmaza egy adott koordinatarol
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    visited[row][col] = true;

    // loop, ahohz hogy megnezzuk a kornyekbeli lepeseket
    for (int d = 0; d < 4; d++) {
        int newRow = row + dx[d];
        int newCol = col + dy[d];

        if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && grid[newRow][newCol] == 0 && !visited[newRow][newCol]) {
            dfs(grid, newRow, newCol, visited);
        }
    }
}

bool checkReachability(const std::vector<std::vector<int>>& grid) {
    // meret lekerese
    int numRows = grid.size();
    int numCols = grid[0].size();

    // latogatott cellak tarolasa
    std::vector<std::vector<bool>> visited(numRows, std::vector<bool>(numCols, false));

    // deep first search kezdete e szelek felol
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if ((row == 0 || row == numRows - 1 || col == 0 || col == numCols - 1) && grid[row][col] == 0 && !visited[row][col]) {
                dfs(grid, row, col, visited);
            }
        }
    }

    // nezzuk meg minden 0 belekerult-e a visited tombbe
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if (grid[row][col] == 0 && !visited[row][col]) {
                return false;
            }
        }
    }

    return true;
}
