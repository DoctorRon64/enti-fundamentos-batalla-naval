#include <iostream>
#include <memory>
#include <vector>
#include <random>

int main() {
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

    //Placing ships for Player 1
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
    }

    //placplayer 2
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
    }

    bool gameOver = false;
    char boardDisplay[BOARD_SIZE] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    
    int currentPlayer = 0;
    bool whenHitGiveAnotherTurn = false;

    while (!gameOver) {
        system("cls");
        if (!whenHitGiveAnotherTurn) {
            currentPlayer = (currentPlayer % 2) + 1;
        }
        else {
            whenHitGiveAnotherTurn = true;
        }

        std::cout << "Jugador 1: " << std::endl;
        for (int i = 0; i < BOARD_SIZE; i++) {
            std::cout << boardDisplay[i];
            std::cout << ' ';
        }
        std::cout << std::endl;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                std::cout << visibleBoardPlayer1[i][j] << ' ';
            }
            std::cout << boardDisplay[i];
            std::cout << '\n';
        }
        std::cout << "----------------------\n";
        std::cout << std::endl;

        std::cout << "Jugador 2: " << std::endl;
        for (int i = 0; i < BOARD_SIZE; i++) {
            std::cout << boardDisplay[i];
            std::cout << ' ';
        }
        std::cout << std::endl;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                std::cout << visibleBoardPlayer2[i][j] << ' ';
            }
            std::cout << boardDisplay[i];
            std::cout << '\n';
        }
        std::cout << "----------------------\n";

        int row, col;
        std::cout << "Player " << currentPlayer << " enter row and column: ";
        std::cin >> col >> row;
        
        if (currentPlayer == 2) {
            if (boardPlayer1[row][col] == '3' || boardPlayer1[row][col] == '4' || boardPlayer1[row][col] == '5' || boardPlayer1[row][col] == '6') {
                visibleBoardPlayer1[row][col] = 'X';
                std::cout << "Hit!\n";

                if (!whenHitGiveAnotherTurn) {
                    whenHitGiveAnotherTurn = true;
                }
                else {
                    whenHitGiveAnotherTurn = false;
                }
            }
            else if (boardPlayer1[row][col] == '~') {
                visibleBoardPlayer1[row][col] = 'O';
                std::cout << "Miss!\n";
                whenHitGiveAnotherTurn = false;
            }
        }
        else if (currentPlayer == 1) {
            if (boardPlayer2[row][col] == '3' || boardPlayer2[row][col] == '4' || boardPlayer2[row][col] == '5' || boardPlayer2[row][col] == '6') {
                visibleBoardPlayer2[row][col] = 'X';
                std::cout << "Hit!\n";
            }
            else if (boardPlayer2[row][col] == '~') {
                visibleBoardPlayer2[row][col] = 'O';
                std::cout << "Miss!\n";
            }
        }

        const int shipCount = 4;
        bool destroyedShips[shipCount] = { false, false, false, false };
        int remainingShipsPlayer1 = shipCount;
        int remainingShipsPlayer2 = shipCount;

        for (int s = 0; s < shipCount; s++) {
            if (!destroyedShips[s]) {
                bool exists = false;
                for (int i = 0; i < BOARD_SIZE && !exists; i++) {
                    for (int j = 0; j < BOARD_SIZE && !exists; j++) {
                        if (boardPlayer1[i][j] == shipSymbols[s]) {
                            exists = true;
                        }
                    }
                }
                if (!exists) {
                    destroyedShips[s] = true;
                    remainingShipsPlayer1--;
                    std::cout << "Player " << currentPlayer << "destroyed ship " << shipSymbols[s] << "!\n";
                }
            }
        }

        for (int s = 0; s < shipCount; s++) {
            if (!destroyedShips[s]) {
                bool exists = false;
                for (int i = 0; i < BOARD_SIZE && !exists; i++) {
                    for (int j = 0; j < BOARD_SIZE && !exists; j++) {
                        if (boardPlayer2[i][j] == shipSymbols[s]) {
                            exists = true;
                        }
                    }
                }
                if (!exists) {
                    destroyedShips[s] = true;
                    remainingShipsPlayer2--;
                    std::cout << "Player " << currentPlayer << "destroyed ship " << shipSymbols[s] << "!\n";
                }
            }
        }

        if (remainingShipsPlayer1 < 0) {
            gameOver = true;
            std::cout << "Player 2 wins!" << std::endl;
        } else if (remainingShipsPlayer2 < 0) {
            gameOver = true;
            std::cout << "Player 1 wins!" << std::endl;
        }

    }

    return 0;
}