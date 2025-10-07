#include "Board.h"

Board::Board() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            grid[i][j].symbol = '~';
            std::cout << grid[i][j].symbol << std::endl;
        }
    }
}