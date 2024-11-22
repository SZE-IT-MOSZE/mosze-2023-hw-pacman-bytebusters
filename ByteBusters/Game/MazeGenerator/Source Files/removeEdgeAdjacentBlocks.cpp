#include "removeEdgeAdjacentBlocks.h"


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
void removeEdgeAdjacentBlocks(std::vector<std::vector<int>>& grid) {
    //meret lekerdezese
    size_t numRows = grid.size();
    size_t numCols = grid[0].size();

    // felso es also folyosok kinullazasa
    for (int col = 0; col < numCols; col++) { //!< A felsõés alsó sorokat kinullázzuk tehát egy pálya határt szabunk a játékosnak
        grid[1][col] = 0;                //!< A felsõ folyosó kinullázása
        grid[numRows - 2][col] = 0;     //!< Az also folyosó kinullázása
    }

    // bal es jobb oldali folyosok kinullazasa
    for (int row = 1; row < numRows - 1; row++) { //!< A jobb és bal oldali folyosók nullázása pálya határ meghúzása miatt
        grid[row][1] = 0;                //!< A bal folyosó nullázása
        grid[row][numCols - 2] = 0;     //!< A jobb folyosó nullázása
    }
}
