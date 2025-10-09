#include <iostream>
#include <memory>
#include <vector>
#include <random>

int main() {
    bool gameOver = false;

    std::cout << "Bienvenido a Batalla naval!" << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << std::endl;

    const int BOARD_SIZE = 10;
    char boardPlayer1[BOARD_SIZE][BOARD_SIZE];
    char boardPlayer2[BOARD_SIZE][BOARD_SIZE];
    char visibleBoardPlayer1[BOARD_SIZE][BOARD_SIZE];
    char visibleBoardPlayer2[BOARD_SIZE][BOARD_SIZE];

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
    std::srand(std::time(0));
    int shipSizes[] = { 3, 4, 5, 6 };
    char shipSymbols[] = { '3', '4', '5', '6' }; //because I cant use cast because the assingment is so basic :(

    for (int i = 0; i < 4; i++) {
        int currentShipSize = shipSizes[i];
        bool placed = false;
        int attempts = 0;

        while (!placed && attempts < 9999) {
            attempts++;

            //Check for Horizontal or Vertical side first
            int dir = std::rand() % 2;
            int row, col = 0;
            if (dir == 0) {
                row = std::rand() % BOARD_SIZE;
                col = std::rand() % (BOARD_SIZE - currentShipSize + 1);
            }
            else {
                row = std::rand() % (BOARD_SIZE - currentShipSize + 1);
                col = std::rand() % BOARD_SIZE;
            }
            
            //Check if is able to place sentire boat 
            bool canPlace = true;
            for (int j = 0; j < currentShipSize; j++) {
                int r = (dir == 1) ? row + j : row;
                int c = (dir == 1) ? col : col + j;

                if (boardPlayer1[r][c] != '~') {
                    canPlace = false;
                    break;
                }
            }

            //if all are free place it:
            if (canPlace) {
                for (int j = 0; j < currentShipSize; j++) {
                    int r = (dir == 1) ? row + j : row;
                    int c = (dir == 1) ? col : col + j;
                    boardPlayer1[r][c] = shipSymbols[i];
                }
                placed = true;
            }
        }
        if (!placed) {
            std::cout << "Failed to place ship of size " << currentShipSize << "\n";
        }
    }

    //For player 2
    for (int i = 0; i < 4; i++) {
        int currentShipSize = shipSizes[i];
        bool placed = false;
        int attempts = 0;

        while (!placed && attempts < 9999) {
            attempts++;

            //Check for Horizontal or Vertical side first
            int dir = std::rand() % 2;
            int row, col = 0;
            if (dir == 0) {
                row = std::rand() % BOARD_SIZE;
                col = std::rand() % (BOARD_SIZE - currentShipSize + 1);
            }
            else {
                row = std::rand() % (BOARD_SIZE - currentShipSize + 1);
                col = std::rand() % BOARD_SIZE;
            }

            //Check if is able to place sentire boat 
            bool canPlace = true;
            for (int j = 0; j < currentShipSize; j++) {
                int r = (dir == 1) ? row + j : row;
                int c = (dir == 1) ? col : col + j;

                if (boardPlayer2[r][c] != '~') {
                    canPlace = false;
                    break;
                }
            }

            //if all are free place it:
            if (canPlace) {
                for (int j = 0; j < currentShipSize; j++) {
                    int r = (dir == 1) ? row + j : row;
                    int c = (dir == 1) ? col : col + j;
                    boardPlayer2[r][c] = shipSymbols[i];
                }
                placed = true;
            }
        }
        if (!placed) {
            std::cout << "Failed to place ship of size " << currentShipSize << "\n";
        }
    }

    //----===== Display boards ========----
    std::cout << "Jugador 1: " << std::endl;
    std::cout << "==========" << std::endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << boardPlayer1[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "----------------------\n";

    std::cout << std::endl;
    std::cout << "Jugador 2: " << std::endl;
    std::cout << "==========" << std::endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << boardPlayer2[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "----------------------\n";

    return 0;
}
