#include <iostream>
#include "printGrid.h"

/**
 * @file printGrid.cpp
 * @brief A printGrid függvény implementációja.
 *
 * Ez a fájl tartalmazza a printGrid függvény implementációját, amely
 * kiírja a rács tartalmát a konzolra.
 */

 /**
  * @brief Kiírja a rács tartalmát a standard kimenetre.
  *
  * Ez a függvény végigiterál a rács minden során, és minden cellájának értékét
  * kiírja a standard kimenetre, szóközzel elválasztva a cellák értékeit.
  *
  * @param grid Egy konstans referencia egy 2D egész számokból álló vektorra, amely a rácsot képviseli.
  */
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int value : row) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
}
