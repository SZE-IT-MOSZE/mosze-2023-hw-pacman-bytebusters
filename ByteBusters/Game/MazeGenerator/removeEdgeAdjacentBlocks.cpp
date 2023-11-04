#include "removeEdgeAdjacentBlocks.h"

/**
 * @file removeEdgeAdjacentBlocks.cpp
 * @brief Implementation of the function to remove blocks adjacent to the edges.
 *
 * This implementation provides the means to nullify the values of grid elements
 * that are directly adjacent to the edge, creating a 'border' of zeros within the grid,
 * one unit away from the actual edge. It operates on the second row and second-last row
 * for horizontal edges, and second column and second-last column for vertical edges.
 */

 /**
  * @brief Nullifies the grid elements adjacent to the edges of a grid.
  *
  * This function will iterate over a 2D grid and set the value of elements
  * that are adjacent to the border of the grid to zero. It affects two rows
  * and two columns: the ones that are one unit away from the actual borders of the grid.
  * The very edges of the grid are left intact.
  *
  * @param grid A reference to a 2D vector of integers representing the grid,
  * where the edge-adjacent blocks will be removed (set to 0).
  */
void removeEdgeAdjacentBlocks(std::vector<std::vector<int>>& grid) {
    // Retrieve the number of rows and columns in the grid.
    int numRows = grid.size();
    int numCols = grid[0].size();

    // Zero out the second and second-to-last rows.
    for (int col = 0; col < numCols; col++) {
        grid[1][col] = 0;             // Top corridor
        grid[numRows - 2][col] = 0;   // Bottom corridor
    }

    // Zero out the second and second-to-last columns.
    for (int row = 1; row < numRows - 1; row++) {
        grid[row][1] = 0;             // Left corridor
        grid[row][numCols - 2] = 0;   // Right corridor
    }
}
