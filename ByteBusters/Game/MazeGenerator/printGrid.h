#pragma once
#ifndef PRINT_GRID_H
#define PRINT_GRID_H

#include <vector>

/**
 * @file printGrid.h
 * @brief Function prototype for printing a grid to the console.
 *
 * Provides the declaration of the printGrid function, which will be
 * used to output the contents of a 2D grid to the console in a readable format.
 */

 /**
  * @brief Prints the contents of a 2D grid to the console.
  *
  * This function iterates over the rows and columns of the provided grid
  * and prints each value, formatting the grid as output.
  *
  * @param grid A constant reference to a 2D vector of integers representing the grid to be printed.
  */
void printGrid(const std::vector<std::vector<int>>& grid);

#endif // PRINT_GRID_H
