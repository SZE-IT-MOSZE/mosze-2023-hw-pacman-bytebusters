#include <iostream>
#include "printGrid.h"

/**
 * @file printGrid.cpp
 * @brief A printGrid f�ggv�ny implement�ci�ja.
 *
 * Ez a f�jl tartalmazza a printGrid f�ggv�ny implement�ci�j�t, amely
 * ki�rja a r�cs tartalm�t a konzolra.
 */

 /**
  * @brief Ki�rja a r�cs tartalm�t a standard kimenetre.
  *
  * Ez a f�ggv�ny v�gigiter�l a r�cs minden sor�n, �s minden cell�j�nak �rt�k�t
  * ki�rja a standard kimenetre, sz�k�zzel elv�lasztva a cell�k �rt�keit.
  *
  * @param grid Egy konstans referencia egy 2D eg�sz sz�mokb�l �ll� vektorra, amely a r�csot k�pviseli.
  */
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int value : row) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
}
