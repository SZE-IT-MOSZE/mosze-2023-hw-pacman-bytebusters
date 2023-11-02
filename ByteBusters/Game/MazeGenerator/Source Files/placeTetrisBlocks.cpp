#include "placeTetrisBlocks.h"
#include <cstdlib> 
#include <ctime>   
//blokk alakok kikialtasa
const std::vector<std::vector<int>> tetrisShapes[] = { //!< A blokk alakok kialak�t�sa ami az adott p�ly�n szerepelni fognak
    // L alak
    {{1, 0}, {1, 0}, {1, 1}}, //!< L alak� blokk
    // T alak
    {{1, 1, 1}, {0, 1, 0}}, //!< T alak� blokk
    // negyzet alak
    {{1, 1}, {1, 1}}, //!< N�gyzet alak� blokk
    // egyenes
    {{1, 1, 1, 1}}, //!< Egyenes alak� blokk
};

void placeTetrisBlocks(std::vector<std::vector<int>>& grid, float targetDensity) {
    //!< A m�ret lek�r�se
    int numRows = grid.size();
    int numCols = grid[0].size();

    //seedeles a veletlenszeruseghez
    //std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //szamoljuk ki hany cellat kell feltolteni
    int maxCells = static_cast<int>(targetDensity * numRows * numCols); //!< Annak a sz�mol�sa, hogy mennyi cell�t kell felt�lten�nk

    int filledCells = 0; //!< Kezdetben 0-a felt�lt�tt cella van

    while (filledCells < maxCells) { //!< A felt�ltes
        
        const std::vector<std::vector<int>>& shape = tetrisShapes[std::rand() % 4]; //!<  Veletlenszer�en v�lasztunk  alakzatot

        // veletlenszeruen valaszt helyet
        int row = std::rand() % (numRows - shape.size() + 1);
        int col = std::rand() % (numCols - shape[0].size() + 1);

        // nezuk meg, ide lerakhatja e
        bool canPlace = true; //!< Azt n�zz�k meg, hogy az adott helyre letehet�-e a v�lasztott blokk
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
        if (canPlace) { //!< Az adott blokk elhelyez�se a p�ly�n 
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
