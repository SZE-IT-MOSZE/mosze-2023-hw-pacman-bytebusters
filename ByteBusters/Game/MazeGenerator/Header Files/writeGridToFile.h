#pragma once
#ifndef WRITE_GRID_TO_FILE_H
#define WRITE_GRID_TO_FILE_H

#include <vector>
#include <string>

/**
 * @file writeGridToFile.cpp
 * @brief A writeGridToFile függvény implementációja.
 *
 * Ez a fájl tartalmazza a writeGridToFile függvény implementációját, amely
 * egy rács tartalmát írja ki egy fájlba.
 */

 /**
  * @brief Kiírja a rács tartalmát egy fájlba.
  *
  * Ez a függvény megnyitja a megadott fájlt, és beleírja a rács tartalmát.
  * Minden sor a rácsból egy új sorba kerül a fájlban, és a cellák értékei
  * szóközzel vannak elválasztva. Amennyiben a fájl nem nyitható meg, hibaüzenetet
  * küld a standard hiba kimenetre.
  *
  * @param grid Egy konstans referencia egy 2D egész számokból álló vektorra, amely a rácsot képviseli.
  * @param filename A fájl neve, amibe a rácsot menteni kívánjuk.
  */
void writeGridToFile(const std::vector<std::vector<int>>& grid, const std::string& filename);

#endif
