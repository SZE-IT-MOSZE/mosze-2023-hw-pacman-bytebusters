#pragma once
#ifndef PLACE_TETRIS_BLOCKS_H
#define PLACE_TETRIS_BLOCKS_H

#include <vector>

/**
 * @file placeTetrisBlocks.h
 * @brief Function prototype for placing Tetris blocks within a grid.
 *
 * Provides the declaration of the placeTetrisBlocks function, which simulates
 * placing Tetris shapes on a grid to reach a target density of occupied cells.
 */

 /**
  * @brief Places Tetris blocks in the grid to reach a target density.
  *
  * This function randomly selects Tetris shapes and positions, attempting to place them
  * onto the grid without overlapping, until the target density of filled cells is reached.
  *
  * @param grid A reference to a 2D vector of integers representing the grid where blocks will be placed.
  * @param targetDensity The desired density of filled cells within the grid.
  */
void placeTetrisBlocks(std::vector<std::vector<int>>& grid, float targetDensity);

#endif // PLACE_TETRIS_BLOCKS_H
