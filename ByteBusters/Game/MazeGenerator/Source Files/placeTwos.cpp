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
    int maxCells = 12; //!< megn�zz�nk, hogy h�ny cell�t kell felt�lten�nk 

    int filledCells = 0; //!< kezdetben a felt�lt�tt cell�k sz�ma 0-a

    while (filledCells < maxCells) {
        // veletlenszeruen valaszt helyet
        int row = std::rand() % numRows; //!< V�ltlen elhelyez�s soronk�nt 
        int col = std::rand() % numCols; //!< V�letlen szer� elhelyez�s oszloponk�nt 

        if (grid[row][col] == 0) {
            grid[row][col] = 2;
            filledCells++;
        }
    }
}
