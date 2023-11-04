// placeTwos.cpp
#include <cstdlib>
#include <ctime>
#include <vector>

/**
 * @file placeTwos.cpp
 * @brief Implementation of the function to place twos in a grid.
 *
 * This file contains the implementation of the function that places a predefined number
 * of two's into random empty locations within a 2D grid.
 */

 /**
  * @brief Randomly places the number 2 into empty cells in a grid.
  *
  * The function first sets a random seed based on the current time to ensure randomness.
  * It then randomly selects positions in the grid to place the number 2, ensuring that
  * it only fills empty cells (cells with a value of 0). It stops once it has placed a
  * specified number of two's into the grid. The number twos will be used for placing down special items later on in the game.
  *
  * @param grid A reference to a 2D vector of integers representing the grid that will be filled with twos.
  */
void placeTwos(std::vector<std::vector<int>>& grid) {
    // Retrieve grid dimensions
    int numRows = grid.size();
    int numCols = grid[0].size();

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Determine the number of cells to fill with the value 2
    int maxCells = 12;

    // Start with zero filled cells
    int filledCells = 0;

    while (filledCells < maxCells) {
        // Randomly select a location
        int row = std::rand() % numRows;
        int col = std::rand() % numCols;

        // If the selected cell is empty, place a 2 and increment the filled cells counter
        if (grid[row][col] == 0) {
            grid[row][col] = 2;
            filledCells++;
        }
    }
}
