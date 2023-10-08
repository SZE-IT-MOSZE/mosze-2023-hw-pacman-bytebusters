#include <iostream>
#include "printGrid.h"

// 2 loop vegig megy a teglalapon
void printGrid(const std::vector<std::vector<int>>& grid) { 
    for (const auto& row : grid) {
        for (int value : row) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
}
