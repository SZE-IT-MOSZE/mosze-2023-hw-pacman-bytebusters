#include "placeTetrisBlocks.h"
#include <cstdlib> 
#include <ctime>   
//blokk alakok kikialtasa
const std::vector<std::vector<int>> tetrisShapes[] = { //!< A blokk alakok kialakítása ami az adott pályán szerepelni fognak
    // L alak
    {{1, 0}, {1, 0}, {1, 1}}, //!< L alakú blokk
    // T alak
    {{1, 1, 1}, {0, 1, 0}}, //!< T alakú blokk
    // negyzet alak
    {{1, 1}, {1, 1}}, //!< Négyzet alakú blokk
    // egyenes
    {{1, 1, 1, 1}}, //!< Egyenes alakú blokk
};



/**
 * @file placeTetrisBlocks.cpp
 * @brief A placeTetrisBlocks függvény implementációja.
 *
 * Ez a fájl tartalmazza a placeTetrisBlocks függvény implementációját, amely
 * a rácson tetris kocka alakú alakzatokat helyez el 1-esek formájában.
 */

 /**
  * @brief Alakzatokat helyez el.
  *
  * Ez a függyvény a rácson tetris kocka alakú alakzatokat helyez el 1-esek formájában. Ezek lesznek később a játékban a falak.
  *
  * @param grid Egy referencia egy 2D egész számokból álló vektorra, amely a rácsot képviseli.
  */
void placeTetrisBlocks(std::vector<std::vector<int>>& grid, float targetDensity) {
    //!< A méret lekérése
    int numRows = grid.size();
    int numCols = grid[0].size();

    //seedeles a veletlenszeruseghez
    //std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //szamoljuk ki hany cellat kell feltolteni
    int maxCells = static_cast<int>(targetDensity * numRows * numCols); //!< Annak a számolása, hogy mennyi cellát kell feltöltenünk

    int filledCells = 0; //!< Kezdetben 0-a feltöltött cella van

    while (filledCells < maxCells) { //!< A feltöltes
        
        const std::vector<std::vector<int>>& shape = tetrisShapes[std::rand() % 4]; //!<  Veletlenszerüen választunk  alakzatot

        // veletlenszeruen valaszt helyet
        int row = std::rand() % (numRows - shape.size() + 1);
        int col = std::rand() % (numCols - shape[0].size() + 1);

        // nezuk meg, ide lerakhatja e
        bool canPlace = true; //!< Azt nézzük meg, hogy az adott helyre letehetõ-e a választott blokk
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
        if (canPlace) { //!< Az adott blokk elhelyezése a pályán 
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
