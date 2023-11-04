#pragma once
#ifndef CHECK_REACHABILITY_H
#define CHECK_REACHABILITY_H

#include <vector>

/**
 * @file checkReachability.h
 * @brief Function prototype to check reachability within a grid.
 *
 * Provides the declaration of the checkReachability function, which will be
 * used to determine if all zeros in a given grid are reachable from the edges
 * without passing through ones.
 */

 /**
  * @brief Check if all zero cells are reachable from the grid edges.
  *
  * This function will traverse the grid starting from the edges looking for zero
  * cells and mark them as visited. If any zero cell is not reachable, it returns false.
  *
  * @param grid A constant reference to a 2D vector of integers representing the grid.
  * @return true if all zero cells are reachable from the grid edges, false otherwise.
  */
bool checkReachability(const std::vector<std::vector<int>>& grid);

#endif // CHECK_REACHABILITY_H
