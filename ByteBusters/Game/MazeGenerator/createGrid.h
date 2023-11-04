#pragma once
#ifndef GRID_H
#define GRID_H

#include <vector>

/**
 * @file createGrid.h
 * @brief Function prototype for creating a 2D grid.
 *
 * Provides the declaration of the createGrid function, which will be
 * used to generate a 2D grid (vector of vectors) with specified dimensions.
 */

 /**
  * @brief Creates a 2D grid with the given dimensions.
  *
  * This function initializes a 2D vector of integers with all elements set to zero.
  *
  * @param a The number of rows in the grid.
  * @param b The number of columns in the grid.
  * @return A 2D vector of integers with dimensions a x b, initialized to zero.
  */
std::vector<std::vector<int>> createGrid(int a, int b);

#endif // GRID_H
