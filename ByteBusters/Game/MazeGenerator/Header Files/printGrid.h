#pragma once
#ifndef PRINT_GRID_H
#define PRINT_GRID_H

#include <vector>


/**
 * @file printGrid.cpp
 * @brief A printGrid fuggveny deklarációja.
 *
 * Ez a fajl tartalmazza a printGrid függvény deklaraciojat, amely
 * kiirja a racs tartalmat a konzolra.
 */

 /**
  * @brief Kiirja a rács tartalmat a standard kimenetre.
  *
  * Ez a fuggvény végigiterál a racs minden soran, és minden cellajanak erteket
  * kirja a standard kimenetre, szokozzel elvalasztva a cella ertekeit.
  *
  * @param grid Egy konstans referencia egy 2D egesz szamokbol allo vektorra, amely a racsot kepviseli.
  */
void printGrid(const std::vector<std::vector<int>>& grid);

#endif