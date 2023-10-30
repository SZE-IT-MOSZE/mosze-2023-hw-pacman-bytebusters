// placeTwos.cpp
#pragma once
#include "placeTwos.h"

void placeTwos(std::vector<std::vector<int>>& grid) {
    // meret lekerese
    int numRows = grid.size();
    int numCols = grid[0].size();

    // seedeles a veletlenszeruseghez
    //std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // szamoljuk ki hany cellat kell feltolteni
    int maxCells = 12;

    int filledCells = 0; // 0 feltott cellaval kezdunk

    while (filledCells < maxCells) {
        // veletlenszeruen valaszt helyet
        int row = std::rand() % numRows;
        int col = std::rand() % numCols;

        if (grid[row][col] == 0) {
            grid[row][col] = 2;
            filledCells++;
        }
    }
}
