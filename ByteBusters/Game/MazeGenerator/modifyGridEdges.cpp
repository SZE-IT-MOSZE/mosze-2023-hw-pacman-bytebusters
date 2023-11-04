#include "modifyGridEdges.h"

/**
 * @file modifyGridEdges.cpp
 * @brief Function to modify the edges of a 2D grid.
 *
 * This function sets the outermost cells of a 2D grid to wall bricks.
 *
 */

 /**
  * @brief Sets the boundary cells of a grid to wall bricks.
  *
  * The first and last rows (top and bottom edges), and the first and last
  * columns (left and right edges) of the grid are set to a value of 1, effectively
  * creating a framed edge around the grid. 
  *
  * @param grid A reference to a 2D vector of integers representing the grid to be modified.
  */
void modifyGridEdges(std::vector<std::vector<int>>& grid) {
    // Query the size of the grid
    int numRows = grid.size();
    if (numRows == 0) return; // Early exit if the grid is empty
    int numCols = grid[0].size();

    // Set the top and bottom rows to 1
    for (int col = 0; col < numCols; col++) {
        grid[0][col] = 1;            // Top edge
        grid[numRows - 1][col] = 1;  // Bottom edge
    }

    // Set the left and right columns to 1, excluding the corners
    // which are already set by the previous loop.
    for (int row = 1; row < numRows - 1; row++) {
        grid[row][0] = 1;            // Left edge
        grid[row][numCols - 1] = 1;  // Right edge
    }
}
