#include "writeGridToFile.h"
#include <fstream>
#include <iostream>
//fajlbairo fuggveny
void writeGridToFile(const std::vector<std::vector<int>>& grid, const std::string& filename) { //!< Ezzel a függvénnyel írjuk fileba a enerált pályát

    std::ofstream outputFile(filename);

    //ha nem tudja megnyitni kuldjon hiba uzenetet
    if (!outputFile.is_open()) { //!< hiba üzenet küldése abban az esetben amikor nem tudjuk megnyitni a generált filet
        std::cerr << "Error: Could not open the file for writing." << std::endl;
        return;
    }

    for (const auto& row : grid) {
        for (int value : row) {
            outputFile << value << ' ';
        }
        outputFile << '\n';

    }
    outputFile.close();
}
