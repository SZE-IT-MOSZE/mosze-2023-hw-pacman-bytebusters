#include "placeTetrisBlocks.h"
#include <cstdlib> 
#include <ctime>

// Define the shapes of the Tetris blocks
const std::vector<std::vector<int>> tetrisShapes[] = {
    // L shape
    {{1, 0}, {1, 0}, {1, 1}},
    // T shape
    {{1, 1, 1}, {0, 1, 0}},
    // Square shape
    {{1, 1}, {1, 1}},
    // Line shape
    {{1, 1, 1, 1}},
};

/**
 * @file placeTetrisBlocks.cpp
 * @brief Function to place Tetris-like blocks in a 2D grid based on a target density.
 *
 * This function attempts to fill a 2D grid with shapes resembling Tetris blocks.
 * The grid is filled until the number of filled cells reaches a number determined by
 * the specified target density. Randomness is used to determine both the type of block
 * and its placement within the grid.
 */

 /**
  * @brief Places Tetris-like blocks into a grid until a specified density is reached.
  *
  * The function iterates over the grid, randomly selecting Tetris block shapes and positions
  * for them within the grid. It checks if a block can be placed in a chosen position without
  * overlapping existing blocks. If it can, the block is placed, and the number of filled cells
  * is incremented. The process repeats until the number of filled cells meets or exceeds the
  * calculated target based on the desired density.
  *
  * @param grid A reference to a 2D vector of integers representing the grid to be filled.
  * @param targetDensity The target density of filled cells in the grid, expressed as a fraction
  *                      of the total number of cells.
  */
void placeTetrisBlocks(std::vector<std::vector<int>>& grid, float targetDensity) {
    // Retrieve the dimensions of the grid
    int numRows = grid.size();
    int numCols = grid[0].size();

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Calculate the number of cells to fill based on the target density
    int maxCells = static_cast<int>(targetDensity * numRows * numCols);

    // Start with zero filled cells
    int filledCells = 0;

    // Continue placing blocks until the target number of cells is filled
    while (filledCells < maxCells) {
        // Randomly select a Tetris shape
        const std::vector<std::vector<int>>& shape = tetrisShapes[std::rand() % 4];

        // Randomly choose a position for the shape within the grid
        int row = std::rand() % (numRows - shape.size() + 1);
        int col = std::rand() % (numCols - shape[0].size() + 1);

        // Check if the block can be placed without overlapping
        bool canPlace = true;
        for (size_t i = 0; i < shape.size(); i++) {
            for (size_t j = 0; j < shape[i].size(); j++) {
                if (shape[i][j] == 1 && grid[row + i][col + j] == 1) {
                    canPlace = false;
                    break;
                }
            }
            if (!canPlace) break;
        }

        // Place the block if possible
        if (canPlace) {
            for (size_t i = 0; i < shape.size(); i++) {
                for (size_t j = 0; j < shape[i].size(); j++) {
                    if (shape[i][j] == 1) {
                        grid[row + i][col + j] = 1;
                        filledCells++;
                    }
                }
            }
        }
    }
}
