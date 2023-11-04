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
  * Each row is followed by a new line character, thus formatting the grid to resemble
  * its actual layout.
  *
  * @param grid A constant reference to a 2D vector of integers representing the grid to be printed.
  */
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int value : row) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
}
