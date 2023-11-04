#pragma once
#ifndef MODIFY_GRID_EDGES_H
#define MODIFY_GRID_EDGES_H

#include <vector>

/**
 * @file modifyGridEdges.h
 * @brief Function prototype for modifying the edges of a grid.
 *
 * Provides the declaration of the modifyGridEdges function, which will be
 * used to set the edges of the given grid to a marked edge.
 */

 /**
  * @brief Modifies the edges of a 2D grid to be non-zero.
  *
  * This function goes through the outermost rows and columns of the grid and sets
  * their values to 1, representing an edge or boundary.
  *
  * @param grid A reference to a 2D vector of integers representing the grid to be modified.
  */
void modifyGridEdges(std::vector<std::vector<int>>& grid);

#endif // MODIFY_GRID_EDGES_H
