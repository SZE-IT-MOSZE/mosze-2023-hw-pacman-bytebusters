#pragma once
#ifndef WRITE_GRID_TO_FILE_H
#define WRITE_GRID_TO_FILE_H

#include <vector>
#include <string>

/**
 * @file writeGridToFile.cpp
 * @brief A writeGridToFile f�ggv�ny implement�ci�ja.
 *
 * Ez a f�jl tartalmazza a writeGridToFile f�ggv�ny implement�ci�j�t, amely
 * egy r�cs tartalm�t �rja ki egy f�jlba.
 */

 /**
  * @brief Ki�rja a r�cs tartalm�t egy f�jlba.
  *
  * Ez a f�ggv�ny megnyitja a megadott f�jlt, �s bele�rja a r�cs tartalm�t.
  * Minden sor a r�csb�l egy �j sorba ker�l a f�jlban, �s a cell�k �rt�kei
  * sz�k�zzel vannak elv�lasztva. Amennyiben a f�jl nem nyithat� meg, hiba�zenetet
  * k�ld a standard hiba kimenetre.
  *
  * @param grid Egy konstans referencia egy 2D eg�sz sz�mokb�l �ll� vektorra, amely a r�csot k�pviseli.
  * @param filename A f�jl neve, amibe a r�csot menteni k�v�njuk.
  */
void writeGridToFile(const std::vector<std::vector<int>>& grid, const std::string& filename);

#endif
