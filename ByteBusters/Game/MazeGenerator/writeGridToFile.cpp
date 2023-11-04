#include "writeGridToFile.h"
#include <fstream>
#include <iostream>

/**
 * @file writeGridToFile.cpp
 * @brief Implementation of the function to write a grid to a file.
 *
 * Provides the definition of the writeGridToFile function, facilitating the
 * output of a 2D grid to a text file. The function ensures each row of the grid
 * is written to a separate line with individual values separated by spaces.
 */

 /**
  * @brief Writes the contents of a 2D grid to a file.
  *
  * Opens a file with the given filename and writes the grid to it. If the file
  * cannot be opened, an error message is printed to the standard error stream.
  * Each value is separated by a space and each row is on a new line in the file.
  *
  * @param grid A constant reference to a 2D vector of integers representing the grid.
  * @param filename A string representing the file's name where the grid will be written.
  */
void writeGridToFile(const std::vector<std::vector<int>>& grid, const std::string& filename) {

    std::ofstream outputFile(filename);

    // Check if the file stream is in a good state (i.e., the file is open and ready for output).
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open the file for writing." << std::endl;
        return;
    }

    // Write each row of the grid to the file.
    for (const auto& row : grid) {
        for (int value : row) {
            outputFile << value << ' ';
        }
        outputFile << '\n';
    }
    outputFile.close(); // Close the file to flush and release the resource.
}
