#include "createGrid.h"
/**
 * @file createGrid.h
 * @brief A createGrid függvény implementacioja.
 *
 * implementalja a createGrid függvényt, amely egy 2D rács létrehozására szolgál.
 */

 /**
  * @brief Függvény prototípusa egy 2D rács létrehozásához.
  *
  * Ez a függvény egy két dimenziós vektort (grid) hoz létre a megadott
  * sorok (a) és oszlopok (b) számával. A rács minden eleme kezdetben nullára
  * van állítva.
  *
  * @param a A rács sorainak száma.
  * @param b A rács oszlopainak száma.
  * @return 2D egész számokból álló vektor, amely a rácsot képviseli,
  * méretei a x b, és minden eleme nullára van inicializálva.
  */

std::vector<std::vector<int>> createGrid(int a, int b) { //!< Egy két dimenzios vektor ami a grid
   
    std::vector<std::vector<int>> grid(a, std::vector<int>(b, 0));
    return grid;
}
