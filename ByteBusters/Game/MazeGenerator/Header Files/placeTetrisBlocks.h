#pragma once
#ifndef PLACE_TETRIS_BLOCKS_H
#define PLACE_TETRIS_BLOCKS_H

#include <vector>


/**
 * @file placeTetrisBlocks.cpp
 * @brief A placeTetrisBlocks függvény deklaracioja.
 *
 * Ez a fájl tartalmazza a placeTetrisBlocks függvény deklaracioja, amely
 * a rácson tetris kocka alakú alakzatokat helyez el 1-esek formájában.
 */

 /**
  * @brief Alakzatokat helyez el.
  *
  * Ez a függyvény a rácson tetris kocka alakú alakzatokat helyez el 1-esek formájában. Ezek lesznek később a játékban a falak.
  *
  * @param grid Egy referencia egy 2D egész számokból álló vektorra, amely a rácsot képviseli.
  */
void placeTetrisBlocks(std::vector<std::vector<int>>& grid, float targetDensity);

#endif
