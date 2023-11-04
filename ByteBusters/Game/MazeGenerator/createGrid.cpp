#include "createGrid.h"

/**
 * @file createGrid.cpp
 * @brief Function to create a 2D grid.
 *
 * This file contains the implementation of the createGrid function which is
 * responsible for creating a two-dimensional vector (grid) with specified dimensions.
 */

 /**
  * @brief Creates a 2D grid of integers initialized to zero.
  *
  * This function initializes a two-dimensional vector (grid) with the given
  * number of rows and columns. All cells in the grid are initially set to zero.
  *
  * @param a The number of rows in the grid.
  * @param b The number of columns in the grid.
  * @return A 2D vector of integers representing the initialized grid.
  */
std::vector<std::vector<int>> createGrid(int a, int b) {
    // Create a 2D vector (grid) with 'a' rows and 'b' columns initialized to 0
    std::vector<std::vector<int>> grid(a, std::vector<int>(b, 0));

    // Return the newly created grid
    return grid;
}
