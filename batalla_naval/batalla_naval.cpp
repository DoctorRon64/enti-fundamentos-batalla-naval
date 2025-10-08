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
   
    //========= Initialize boards ======
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            boardPlayer1[i][j] = '~';
            boardPlayer2[i][j] = '~';
        }
    }

    //===== Display boards ========
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

    int shipSizes[] = { 3, 4, 5, 6 };
    std::srand(std::time(NULL));

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; ++j) {
            if (boardPlayer1[i][j] == '~') {
                //if (ship == 0) return;
                //ship--;
                //board[i][j] = shipChar;
            }
        }
    }



    return 0;
}
