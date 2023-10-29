#include "generateMaze.h"

//#define DEBUG

bool generateMaze() {
    
    std::string folderPath = "Fields\\";
    int files = 1;
    int height = 15;
    int width = 20;
    double targetDensity = 0.2;
    while (files <= 20) {
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