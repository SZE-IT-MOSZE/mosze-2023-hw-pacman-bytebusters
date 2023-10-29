#include <iostream>
#include <sstream>
#include "createGrid.h"
#include "printGrid.h"
#include "modifyGridEdges.h"
#include "placeTetrisBlocks.h"
#include "removeEdgeAdjacentBlocks.h"
#include "writeGridToFile.h"
#include "checkReachability.h"
#include "placeTwos.cpp"

int main() {
    std::string folderPath = "Fields/";
    int files = 1;
    int a = 20;
    int b = 15;
    double targetDensity = 0.2;
    while (files <= 2) {
        std::vector<std::vector<int>> grid = createGrid(a, b);

        placeTetrisBlocks(grid, targetDensity);
        removeEdgeAdjacentBlocks(grid);


        std::ostringstream filenameStream;
        filenameStream << folderPath << "\\" << files << ".txt";
        std::string filename = filenameStream.str();

        bool isReachable = checkReachability(grid);
        if (isReachable) {
            modifyGridEdges(grid);
            placeTwos(grid);
            std::cout << "Grid: " << files << std::endl;
            printGrid(grid);
            writeGridToFile(grid, filename);
            std::cout << "Saved grid " << files << " to " << filename << std::endl;
            files++;
        }

    }
    return 0;
}
