#pragma once
#ifndef REMOVE_EDGE_ADJACENT_BLOCKS_H
#define REMOVE_EDGE_ADJACENT_BLOCKS_H

#include <vector>

/**
 * @file removeEdgeAdjacentBlocks.cpp
 * @brief A removeEdgeAdjacentBlocks f�ggv�ny implement�ci�ja.
 *
 * Ez a f�jl tartalmazza a removeEdgeAdjacentBlocks f�ggv�ny implement�ci�j�t, amely
 * a r�cson a sz�lek melletti sorokb�l t�rli a falakat, �gy egy k�r folyos�t hoz l�tre.
 */

 /**
  * @brief K�rfolyos�t alaki�t ki
  *
  *
  * Ez a f�jl tartalmazza a removeEdgeAdjacentBlocks f�ggv�ny implement�ci�j�t, amely
  * a r�cson a sz�lek melletti sorokb�l t�rli a falakat, �gy egy k�r folyos�t hoz l�tre.
  *
  *
  * @param grid Egy referencia egy 2D eg�sz sz�mokb�l �ll� vektorra, amely a r�csot k�pviseli.
  */
void removeEdgeAdjacentBlocks(std::vector<std::vector<int>>& grid);

#endif

