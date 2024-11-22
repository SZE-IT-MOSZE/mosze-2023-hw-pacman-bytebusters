#include "placeTwos.h"
#include <cstdlib>
#include <ctime>

/**
 * @file placeTwos.cpp
 * @brief A placeTwos függvény implementációja.
 *
 * Ez a fájl tartalmazza a placeTwos függvény implementációját, amely
 * "2"-ket helyez el véletlenszerűen egy rácsban.
 */

 /**
  * @brief "2" helyez el a rácsban.
  *
  * Ez a függvény véletlenszerűen választ cellákat a rácsban, és elhelyezi
  * bennük a "2" értéket, amíg el nem éri a meghatározott számú cellát.
  * A függvény célja, hogy szórásszerűen elhelyezzen értékeket a rácsban.
  *
  * @param grid Egy referencia egy 2D egész számokból álló vektorra, amely a rácsot képviseli.
  */
void placeTwos(std::vector<std::vector<int>>& grid) {
    size_t numRows = grid.size();
    size_t numCols = grid[0].size();

    // Random inicializálása
    //std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Megnézzük, hogy hány cellát kell feltöltenünk
    int maxCells = 12; // A feltöltendő cellák maximális száma

    int filledCells = 0; // Kezdetben a feltöltött cellák száma nulla

    while (filledCells < maxCells) {
        // Véletlenszerűen választ helyet
        int row = std::rand() % numRows; // Véletlenszerűen választ soronként
        int col = std::rand() % numCols; // Véletlenszerűen választ oszloponként

        // Ha a cella üres, akkor elhelyezzük benne hogy "2"
        if (grid[row][col] == 0) {
            grid[row][col] = 2;
            filledCells++;
        }
    }
}
