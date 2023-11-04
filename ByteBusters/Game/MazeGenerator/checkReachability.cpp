#include "checkReachability.h"
#include <vector>

/**
 * @file checkReachability.cpp
 * @brief Function to check if all empty spaces are reachable from the grid's edges.
 *
 * Implements a depth-first search (DFS) to traverse the grid and mark visited empty cells.
 * It is used to determine if all accessible cells are reachable from the edges of the grid.
 */

 /**
  * Performs a depth-first search on the grid starting from the specified cell.
  *
  * @param grid The grid represented as a 2D vector of integers.
  * @param row The row index of the starting cell for DFS.
  * @param col The column index of the starting cell for DFS.
  * @param visited A 2D vector to track visited cells.
  */
void dfs(const std::vector<std::vector<int>>& grid, int row, int col, std::vector<std::vector<bool>>& visited) {
    const int numRows = grid.size();
    const int numCols = grid[0].size();

    // Directions in which DFS will move: up, down, left, right
    const int dx[] = { -1, 1, 0, 0 };
    const int dy[] = { 0, 0, -1, 1 };

    // Mark the current cell as visited
    visited[row][col] = true;

    // Explore the neighboring cells
    for (int d = 0; d < 4; d++) {
        int newRow = row + dx[d];
        int newCol = col + dy[d];

        // Check if the new position is within bounds and not visited
        if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && grid[newRow][newCol] == 0 && !visited[newRow][newCol]) {
            dfs(grid, newRow, newCol, visited);
        }
    }
}

/**
 * Checks if all zero-valued cells in the grid are reachable from its edges.
 *
 * @param grid The grid represented as a 2D vector of integers.
 * @return A boolean indicating if all empty cells (zeros) are reachable from the grid's edges.
 */
bool checkReachability(const std::vector<std::vector<int>>& grid) {
    const int numRows = grid.size();
    const int numCols = grid[0].size();

    // Initialize a 2D vector to track visited cells
    std::vector<std::vector<bool>> visited(numRows, std::vector<bool>(numCols, false));

    // Start DFS from the edge cells that are empty (zero-valued)
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if ((row == 0 || row == numRows - 1 || col == 0 || col == numCols - 1) && grid[row][col] == 0 && !visited[row][col]) {
                dfs(grid, row, col, visited);
            }
        }
    }

    // Check if there are any zero-valued cells that were not visited
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if (grid[row][col] == 0 && !visited[row][col]) {
                return false; // Found an unreachable empty cell
            }
        }
    }

    // All empty cells are reachable if none were found unreachable
    return true;
}
