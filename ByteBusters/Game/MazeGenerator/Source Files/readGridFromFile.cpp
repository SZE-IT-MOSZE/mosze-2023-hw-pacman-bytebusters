// readGridFromFile.cpp
/*#include "readGridFromFile.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

std::vector<std::vector<int>> readGridFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file for reading." << std::endl;
        return {}; // Return an empty vector to indicate an error
    }

    std::vector<std::vector<int>> grid;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::vector<int> row;
        std::istringstream iss(line);
        int value;
        while (iss >> value) {
            row.push_back(value);
        }
        grid.push_back(row);
    }

    inputFile.close();
    return grid;
}
*/