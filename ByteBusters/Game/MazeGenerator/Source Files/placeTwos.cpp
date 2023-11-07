// placeTwos.cpp
#pragma once
#include "placeTwos.h"

void placeTwos(std::vector<std::vector<int>>& grid) {
    // meret lekerese
    int numRows = grid.size();
    int numCols = grid[0].size();

    // seedeles a veletlenszeruseghez
    //std::
    // (static_cast<unsigned int>(std::time(nullptr)));

    // szamoljuk ki hany cellat kell feltolteni
    int maxCells = 12; //!< megnézzünk, hogy hány cellát kell feltöltenünk 

    int filledCells = 0; //!< kezdetben a feltöltött cellék száma 0-a

    while (filledCells < maxCells) {
        // veletlenszeruen valaszt helyet
        int row = std::rand() % numRows; //!< Véltlen elhelyezés soronként 
        int col = std::rand() % numCols; //!< Véletlen szerû elhelyezés oszloponként 

        if (grid[row][col] == 0) {
            grid[row][col] = 2;
            filledCells++;
        }
    }
}
