#include "modifyGridEdges.h"

/**
 * @file modifyGridEdges.cpp
 * @brief A modifyGridEdges függvény implementációja.
 *
 * Ez a fájl tartalmazza a modifyGridEdges függvény implementációját, amely
 * a rács szélén lévő cellákat módosítja.
 */

 /**
  * @brief Módosítja a rács szélén lévő cellákat.
  *
  * Ez a függvény a rács szélén lévő cellák értékét módosítja egy előre meghatározott értékre.
  * Különösen a rács első és utolsó sorában, valamint az első és utolsó oszlopában
  * végzi ezt a műveletet, létrehozva ezzel egy keretet a rács számára.
  *
  * @param grid Egy referencia egy 2D egész számokból álló vektorra, amely a rácsot képviseli.
  */
void modifyGridEdges(std::vector<std::vector<int>>& grid) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    // A felső és alsó sorok kinullázása
    for (int col = 0; col < numCols; col++) {
        grid[0][col] = 1;                // A felső sor
        grid[numRows - 1][col] = 1;      // Az alsó sor
    }

    // A bal és jobb oldal kinullázása
    for (int row = 1; row < numRows - 1; row++) {
        grid[row][0] = 1;                // A bal oldal
        grid[row][numCols - 1] = 1;      // A jobb oldal
    }
}
