#include <iostream>
#include <sstream>
#include "createGrid.h"
#include "printGrid.h"
#include "modifyGridEdges.h"
#include "placeTetrisBlocks.h"
#include "removeEdgeAdjacentBlocks.h"
#include "writeGridToFile.h"
#include "checkReachability.h"

int main() {
    std::string folderPath = "D:/Sulesz/Mosze/Maze/mazegenerator/mazegenerator/fields";
    int files = 1;
    while (files != 21) {
        int a = 35; // Meret beallitasa
        int b = 28;
        float targetDensity = 0.265; //suruseg beallitasa
        std::string filename = "grid_output.txt"; // mi legyen a kimenti fajlok neve? inicializalas?, 1 filehoz kellett, 20, hoz annyira nem, de enelkul a sor nelkul nem mukodik nem ertem miert lol

        //tomb generalasa 00000
        //                00000
        //                00000
        std::vector<std::vector<int>> grid = createGrid(a, b);

        // szelek 1-esse valtozatasa
        modifyGridEdges(grid);

        // tetris blokkok lerakasa a suruseg elereseig
        placeTetrisBlocks(grid, targetDensity);

        // a szelek melletti folyoso kialakitasa
        removeEdgeAdjacentBlocks(grid);

        // nezzuk meg, hogy minden 0 elerheto e
        bool isReachable = checkReachability(grid);

        // ujra legyen minden szelso blokk 1-es, hatha megvaltozott
        modifyGridEdges(grid);

        // kiiras teszteleshez
        //printGrid(grid);

        // irjuk ki fileokba
        if (isReachable) {
            std::ostringstream filenameStream;
            filenameStream << folderPath << "/grid" << files << ".txt";
            filename = filenameStream.str();
            writeGridToFile(grid, filename);
            std::cout << "Saved grid " << files << " to " << filename << std::endl;
            files++;
        }
    }
    return 0;
}
