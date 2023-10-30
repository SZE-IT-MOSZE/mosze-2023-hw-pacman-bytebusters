#include "placeTetrisBlocks.h"
#include <cstdlib> 
#include <ctime>   
//blokk alakok kikialtasa
const std::vector<std::vector<int>> tetrisShapes[] = {
    // L alak
    {{1, 0}, {1, 0}, {1, 1}},
    // T alak
    {{1, 1, 1}, {0, 1, 0}},
    // negyzet alak
    {{1, 1}, {1, 1}},
    // egyenes
    {{1, 1, 1, 1}},
};

void placeTetrisBlocks(std::vector<std::vector<int>>& grid, float targetDensity) {
    // meret lekerese
    int numRows = grid.size();
    int numCols = grid[0].size();

    //seedeles a veletlenszeruseghez
    //std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //szamoljuk ki hany cellat kell feltolteni
    int maxCells = static_cast<int>(targetDensity * numRows * numCols);

    int filledCells = 0; //0 feltott cellaval kezdunk

    while (filledCells < maxCells) { //feltoltes
        // veletlenszeruen valaszt alakit
        const std::vector<std::vector<int>>& shape = tetrisShapes[std::rand() % 4];

        // veletlenszeruen valaszt helyet
        int row = std::rand() % (numRows - shape.size() + 1);
        int col = std::rand() % (numCols - shape[0].size() + 1);

        // nezuk meg, ide lerakhatja e
        bool canPlace = true;
        for (size_t i = 0; i < shape.size(); i++) {
            for (size_t j = 0; j < shape[i].size(); j++) {
                if (shape[i][j] == 1 && grid[row + i][col + j] == 1) {
                    canPlace = false;
                    break;
                }
            }
            if (!canPlace) {
                break;
            }
        }

        // elhelyezes
        if (canPlace) {
            for (size_t i = 0; i < shape.size(); i++) {
                for (size_t j = 0; j < shape[i].size(); j++) {
                    if (shape[i][j] == 1) {
                        grid[row + i][col + j] = 1;
                        filledCells++;
                    }
                }
            }
        }
    }
}
