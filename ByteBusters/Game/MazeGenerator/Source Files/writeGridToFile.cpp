#include "writeGridToFile.h"
#include <fstream>
#include <iostream>
//fajlbairo fuggveny
void writeGridToFile(const std::vector<std::vector<int>>& grid, const std::string& filename) {

    std::ofstream outputFile(filename);

    //ha nem tudja megnyitni kuldjon hiba uzenetet
    if (!outputFile.is_open()) {
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
