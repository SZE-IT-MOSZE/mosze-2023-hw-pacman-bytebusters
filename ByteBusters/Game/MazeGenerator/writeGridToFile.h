#pragma once
#ifndef WRITE_GRID_TO_FILE_H
#define WRITE_GRID_TO_FILE_H

#include <vector>
#include <string>

/**
 * @file writeGridToFile.h
 * @brief Function prototype for writing a grid to a file.
 *
 * This header provides the declaration of the writeGridToFile function, which
 * enables writing the contents of a 2D grid to a specified file. The output
 * file will contain the grid values in a format suitable for visual inspection
 * or further processing.
 */

 /**
  * @brief Writes the contents of a 2D grid to a file.
  *
  * This function takes a grid as a 2D vector of integers and a filename as a string
  * and writes the grid to the specified file. Each line in the file corresponds to a
  * row in the grid. Values within the same row are separated by a space.
  *
  * @param grid A constant reference to a 2D vector of integers representing the grid to be written.
  * @param filename A string representing the name of the file to which the grid will be written.
  */
void writeGridToFile(const std::vector<std::vector<int>>& grid, const std::string& filename);

#endif // WRITE_GRID_TO_FILE_H
