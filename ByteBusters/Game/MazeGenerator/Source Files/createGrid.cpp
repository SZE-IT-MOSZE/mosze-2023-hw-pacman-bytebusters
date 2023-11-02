#include "createGrid.h"

std::vector<std::vector<int>> createGrid(int a, int b) { //!< Egy két dimenzios vektor ami a grid
   
    std::vector<std::vector<int>> grid(a, std::vector<int>(b, 0));
    return grid;
}
