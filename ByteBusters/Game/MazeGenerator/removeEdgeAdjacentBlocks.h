#pragma once
#ifndef REMOVE_EDGE_ADJACENT_BLOCKS_H
#define REMOVE_EDGE_ADJACENT_BLOCKS_H

#include <vector>

/**
 * @file removeEdgeAdjacentBlocks.h
 * @brief Function prototype for removing edge-adjacent blocks from a grid.
 *
 * Provides the declaration of the removeEdgeAdjacentBlocks function, which will be
 * used to find and remove blocks that are adjacent to the edge of the grid.
 */

 /**
  * @brief Removes blocks from the grid that are adjacent to the edges.
  *
  * This function examines each cell in the grid and removes any filled cells
  * that are adjacent to an edge, setting them back to zero. A walking corridor should be established between the
  * shapes and the outer wall.
  *
  * @param grid A reference to a 2D vector of integers representing the grid from which edge-adjacent blocks will be removed.
  */
void removeEdgeAdjacentBlocks(std::vector<std::vector<int>>& grid);

#endif // REMOVE_EDGE_ADJACENT_BLOCKS_H
