#include "writeGridToFile.h"
#include <fstream>
#include <iostream>

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
  * szóközzel vannak elválasztva.
  * Amennyiben a fájl nem nyitható meg, hibaüzenetet küld a standard hiba kimenetre.
  *
  * @param grid Egy konstans referencia egy 2D egész számokból álló vektorra, amely a rácsot képviseli.
  * @param filename A fájl neve, amibe a rácsot menteni kívánjuk.
  */
void writeGridToFile(const std::vector<std::vector<int>>& grid, const std::string& filename) {
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open the file for writing.\n";
        return;
    }

    for (size_t i = 0; i < grid.size(); ++i) {
        for (int value : grid[i]) {
            outputFile << value << ' ';
        }
        //newline character minden sor végére kivéve az utolsóra
        if (i < grid.size() - 1) {
            outputFile << '\n';
        }
    }
    outputFile.close();
}
