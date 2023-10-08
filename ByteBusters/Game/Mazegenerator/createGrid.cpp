#include "createGrid.h"

std::vector<std::vector<int>> createGrid(int a, int b) {
    // 2dimenzios vektor a grid
    std::vector<std::vector<int>> grid(a, std::vector<int>(b, 0));
    return grid;
}
