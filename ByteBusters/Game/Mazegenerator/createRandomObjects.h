#pragma once
#ifndef CREATERANDOMOBJECTS_H
#define CREATERANDOMOBJECTS_H

#include <vector>

// Declare the function prototype
void createRandomObjects(std::vector<std::vector<char>>& grid);

// Function to set the character for the objects ('3' or '4')
void setObjectChar(std::vector<std::vector<char>>& grid, char objectChar);

#endif // CREATERANDOMOBJECTS_H
