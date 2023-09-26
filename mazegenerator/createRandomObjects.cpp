#include "createRandomObjects.h"
#include <random>
#include <ctime>
#include <vector>

namespace {
    // Function to place random objects consisting of 4 squares
    void placeObjects(std::vector<std::vector<char>>& grid) {
        int height = grid.size();
        int width = grid[0].size();

        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        while (true) {
            int i, j;

            // Find a random '0' position in the grid
            do {
                i = 1 + std::rand() % (height - 2);
                j = 1 + std::rand() % (width - 2);
            } while (grid[i][j] != '0');

            // Place a random object consisting of 4 squares
            grid[i][j] = grid[i + 1][j] = grid[i + 2][j] = grid[i + 3][j] = '4';

            // Break the loop if you've placed enough objects
            if (--numObjects == 0) {
                break;
            }
        }
    }

    int numObjects = 0; // Track the number of objects to be placed
}

// Function to create random objects in the grid
void createRandomObjects(std::vector<std::vector<char>>& grid) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    // Calculate the number of cells that objects should occupy (approximately 35%)
    int totalCells = numRows * numCols;
    numObjects = totalCells * 0.35;

    // Call the function to place objects
    placeObjects(grid);
}

// Function to set the character for the objects ('3' or '4')
void setObjectChar(std::vector<std::vector<char>>& grid, char objectChar) {
    if (objectChar == '3') {
        placeObjects(grid);
    }
    else if (objectChar == '4') {
        placeObjects(grid);
    }
}
