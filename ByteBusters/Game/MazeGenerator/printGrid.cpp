#include <iostream>
#include "printGrid.h"

/**
 * @file printGrid.cpp
 * @brief Implementation of the function to print a grid to the console.
 *
 * This implementation provides the means to display the contents of a 2D integer grid
 * on the standard output, with each value separated by a space and each row on a new line.
 */

 /**
  * @brief Prints the content of a 2D grid to the standard output.
  *
  * Iterates over each row of the 2D vector, printing each value separated by a space.
  * Each row is followed by a new line character except the last row, thus formatting the grid to resemble
  * its actual layout.
  *
  * @param grid A constant reference to a 2D vector of integers representing the grid to be printed.
  */
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (size_t i = 0; i < grid.size(); ++i) {
        for (int value : grid[i]) {
            std::cout << value << ' ';
        }
        // Add a newline character except after the last row
        if (i < grid.size() - 1) {
            std::cout << '\n';
        }
    }
}

