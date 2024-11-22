#pragma once
#ifndef REMOVE_EDGE_ADJACENT_BLOCKS_H
#define REMOVE_EDGE_ADJACENT_BLOCKS_H

#include <vector>

/**
 * @file removeEdgeAdjacentBlocks.cpp
 * @brief A removeEdgeAdjacentBlocks függvény implementációja.
 *
 * Ez a fájl tartalmazza a removeEdgeAdjacentBlocks függvény implementációját, amely
 * a rácson a szélek melletti sorokból törli a falakat, így egy kör folyosót hoz létre.
 */

 /**
  * @brief Körfolyosót alakiít ki
  *
  *
  * Ez a fájl tartalmazza a removeEdgeAdjacentBlocks függvény implementációját, amely
  * a rácson a szélek melletti sorokból törli a falakat, így egy kör folyosót hoz létre.
  *
  *
  * @param grid Egy referencia egy 2D egész számokból álló vektorra, amely a rácsot képviseli.
  */
void removeEdgeAdjacentBlocks(std::vector<std::vector<int>>& grid);

#endif

