#include "generateMaze.h"

#define MAPS 10

//#define DEBUG
/**
 * @file generateMaze.h
 * @brief A generateMaze fuggveny implementacioja.
 *
 * implementalja a generateMaze fuggvenyt, amely felelos palyak generalasert es
 * mentesert fajlokba.
 */

 /**
  * @brief Fuggveny prototipusa a palya generalashoz.
  *
  * Ez a fuggveny labirintusokat general különböző Tetris alakzatokbol, majd
  * ellenorzi az elerhetoseget es modositja a racs szeleit. Ha a labirintus
  * megfelelo, elmenti azt egy fajlba.
  *
  * @return Igaz, ha a labirintus generalas sikeres volt.
  */

bool generateMaze() {
    
    std::string folderPath = "Fields\\";
    int files = 1;
    int height = 15;
    int width = 20;
    float targetDensity = 0.2f;
    while (files <= MAPS) {
        std::vector<std::vector<int>> grid = createGrid(height, width);

        placeTetrisBlocks(grid, targetDensity);
        removeEdgeAdjacentBlocks(grid);


        std::ostringstream filenameStream;
        filenameStream << folderPath << files << ".txt";
        std::string filename = filenameStream.str();

#ifdef DEBUG
        std::cout << filename << std::endl;
#endif // DEBUG


        

        bool isReachable = checkReachability(grid);
        if (isReachable) {
            modifyGridEdges(grid);
            placeTwos(grid);
#ifdef DEBUG
            std::cout << "Grid: " << files << std::endl;
            printGrid(grid);     
#endif // DEBUG
            writeGridToFile(grid, filename);
#ifdef DEBUG
            std::cout << "Saved grid " << files << " to " << filename << std::endl;
#endif // DEBUG
            files++;
        }

    }

	return true;
}