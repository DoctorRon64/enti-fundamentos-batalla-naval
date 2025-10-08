#include <iostream>
#include <memory>
#include <vector>
#include <random>

int main() {
    bool gameOver = false;

    std::cout << "Bienvenido a Batalla naval!" << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << std::endl;

    char boardPlayer1[10][10];
    char boardPlayer2[10][10];
    char visibleBoardPlayer1[10][10];
    char visibleBoardPlayer2[10][10];

    //-----========= Initialize boards ======-----
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            boardPlayer1[i][j] = '~';
            boardPlayer2[i][j] = '~';
            visibleBoardPlayer1[i][j] = '~';
            visibleBoardPlayer2[i][j] = '~';
        }
    }

    //------========== Place Ships ========-------
    int shipSizes[] = { 3, 4, 5, 6 };
    char shipSymbols[] = { '3', '4', '5', '6' }; //because I cant use cast because the assingment is so basic :(

    for (int i = 0; i < 4; i++) {
        int currentShipSize = shipSizes[i];
        bool placed = false;
        int attempts = 0;

        //Based on that orientation and the ship length, choose a random starting row and column such that the ship will fit inside the 10×10 grid.
        //Check every cell along the intended ship path to ensure none are already occupied.
        //If all cells are free, mark those cells as containing the ship and stop trying for this ship.
        //If any cell is occupied, discard this attempt and try a new random position / orientation.

        while (!placed) {
            //int dir = std::rand() % 2; //randomized vertical or horizontal;
            int dir = 0;

            if (dir == 0) {
                int randomRow = std::rand() % (10 - currentShipSize);
                int randomColomn = std::rand() % (10 - currentShipSize);

                for (int j = 0; j < currentShipSize; j++) {
                    boardPlayer1[randomRow][randomColomn] = shipSymbols[i];
                    randomColomn++;
                }

                placed = true;
            } else {
                int randomPos = std::rand() % 10;

            }
        }
    }

    //----===== Display boards ========----
    std::cout << "Jugador 1: " << std::endl;
    std::cout << "==========" << std::endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << boardPlayer1[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Jugador 2: " << std::endl;
    std::cout << "==========" << std::endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << boardPlayer2[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}
