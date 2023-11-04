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

/**
 * @file main.cpp
 * @brief The main driver of the grid generation and manipulation program.
 *
 * This program generates grids filled with Tetris blocks, checks for reachability,
 * places additional blocks, and outputs the final grid state to a file.
 */

int main() {
    // Define the directory where the grid files will be saved.
    std::string folderPath = "Fields/";

    // Initialize variables for file naming and grid properties.
    int files = 1;             // Counter for the number of files generated.
    int a = 20;                // Number of rows in the grid.
    int b = 15;                // Number of columns in the grid.
    double targetDensity = 0.2; // Target density for Tetris block placement.

    // Loop to create multiple grid files.
    while (files <= 2) {
        // Create a grid with dimensions a x b filled with zeros.
        std::vector<std::vector<int>> grid = createGrid(a, b);

        // Place Tetris blocks in the grid until the target density is reached.
        placeTetrisBlocks(grid, targetDensity);
        // Remove blocks that are adjacent to the grid's edges.
        removeEdgeAdjacentBlocks(grid);

        // Construct the filename for the current grid.
        std::ostringstream filenameStream;
        filenameStream << folderPath << "\\" << files << ".txt";
        std::string filename = filenameStream.str();

        // Check if all empty spaces are reachable from the grid's edges.
        bool isReachable = checkReachability(grid);
        if (isReachable) {
            // Modify the grid's edges if all 0-s were reached.
            modifyGridEdges(grid);
            // Place additional twos in the grid.
            placeTwos(grid);
            // Print the current grid to the console.
            std::cout << "Grid: " << files << std::endl;
            printGrid(grid);
            // Write the current grid to the specified file.
            writeGridToFile(grid, filename);
            // Inform the user that the grid has been saved.
            std::cout << "Saved grid " << files << " to " << filename << std::endl;
            // Increment the file counter after successful grid creation and saving.
            files++;
        }
        // If the grid is not reachable, the while loop will continue without incrementing 'files',
        // resulting in another attempt to generate a valid grid until the limit is reached.
    }
    // Return 0 to signify that the program has executed successfully.
    return 0;
}
