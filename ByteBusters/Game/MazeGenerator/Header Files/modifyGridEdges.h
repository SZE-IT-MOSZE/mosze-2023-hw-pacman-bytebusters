#pragma once
#ifndef MODIFY_GRID_EDGES_H
#define MODIFY_GRID_EDGES_H

#include <vector>


/**
 * @file modifyGridEdges.cpp
 * @brief A modifyGridEdges függvény implementációja.
 *
 * Ez a fájl tartalmazza a modifyGridEdges függvény implementációját, amely
 * módosítja a grid széleit, azaz beállítja azok értékét egy adott számra.
 */

 /**
  * @brief Módosítja a grid széleit.
  *
  * Ez a függvény a grid széleit (az első és az utolsó sort, valamint az első és az utolsó oszlopot)
  * módosítja úgy, hogy azokat egy adott értékre (jelen esetben 1-re) állítja. A folyamat célja,
  * hogy a rács egy kerettel rendelkezzen.
  *
  * @param grid Egy referencia egy 2D egész számokból álló vektorra, amely a rácsot képviseli.
  */

void modifyGridEdges(std::vector<std::vector<int>>& grid);

#endif 
