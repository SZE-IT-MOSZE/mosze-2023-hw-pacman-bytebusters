#pragma once
#ifndef PRINT_GRID_H
#define PRINT_GRID_H

#include <vector>


/**
 * @file printGrid.cpp
 * @brief A printGrid fuggveny deklar�ci�ja.
 *
 * Ez a fajl tartalmazza a printGrid f�ggv�ny deklaraciojat, amely
 * kiirja a racs tartalmat a konzolra.
 */

 /**
  * @brief Kiirja a r�cs tartalmat a standard kimenetre.
  *
  * Ez a fuggv�ny v�gigiter�l a racs minden soran, �s minden cellajanak erteket
  * kirja a standard kimenetre, szokozzel elvalasztva a cella ertekeit.
  *
  * @param grid Egy konstans referencia egy 2D egesz szamokbol allo vektorra, amely a racsot kepviseli.
  */
void printGrid(const std::vector<std::vector<int>>& grid);

#endif