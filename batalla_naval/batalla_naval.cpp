#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>

int main() {
	std::cout << "Bienvenido a Batalla naval!" << std::endl;
	std::cout << "================================" << std::endl;
	std::cout << std::endl;

	const int BOARD_SIZE = 10;
	const int SHIP_COUNT = 4;
	const char WATER = '~';
	const char HIT_MARK = 'X';
	const char MISS_MARK = 'O';

	char boardPlayer1[BOARD_SIZE][BOARD_SIZE];
	char boardPlayer2[BOARD_SIZE][BOARD_SIZE];
	char visibleBoardPlayer1[BOARD_SIZE][BOARD_SIZE];
	char visibleBoardPlayer2[BOARD_SIZE][BOARD_SIZE];

	//-----========= Initialize boards ======-----
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			boardPlayer1[i][j] = WATER;
			boardPlayer2[i][j] = WATER;
			visibleBoardPlayer1[i][j] = WATER;
			visibleBoardPlayer2[i][j] = WATER;
		}
	}

	//------========== Place Ships ========-------
	std::srand((unsigned int)std::time(0));
	int shipSizes[SHIP_COUNT] = { 3, 4, 5, 6 };
	char shipSymbols[SHIP_COUNT];
	for (int i = 0; i < SHIP_COUNT; ++i) {
		shipSymbols[i] = '0' + shipSizes[i]; //if only static_cast<> :(
	}

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

				if (boardPlayer1[r][c] != WATER) {
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

				if (boardPlayer2[r][c] != WATER) {
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
	int currentPlayer = 0;
	bool whenHitGiveAnotherTurn = false;
	bool showBoatsOnFirstRound = true;

	//============= View boats ================
	std::cout << "Jugador 1: " << std::endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		std::cout << i; //type casting
		std::cout << ' ';
	}
	std::cout << std::endl;
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			std::cout << boardPlayer1[i][j] << ' ';
		}
		std::cout << i;
		std::cout << '\n';
	}
	std::cout << "----------------------\n";
	std::cout << std::endl;

	std::cout << "PRESS ENTER TO CLEAR THE BOARD";
	std::string temp;
	std::getline(std::cin, temp);
	system("cls");
	std::cout << "PRESS ENTER TO SEE THE NEXT PLAYERS BOARD";
	std::getline(std::cin, temp);
	std::cout << std::endl;

	// print board 2
	std::cout << "Jugador 2: " << std::endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		std::cout << i; //type casting
		std::cout << ' ';
	}
	std::cout << std::endl;
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			std::cout << boardPlayer2[i][j] << ' ';
		}
		std::cout << i;
		std::cout << '\n';
	}
	std::cout << "----------------------\n";
	std::cout << std::endl;
	std::cout << "PRESS ENTER START THE GAME!!!";
	std::getline(std::cin, temp);

	while (!gameOver) {
		system("cls");
		if (!whenHitGiveAnotherTurn) {
			currentPlayer = (currentPlayer % 2) + 1;
		}
		else {
			whenHitGiveAnotherTurn = false;
		}

		//=== print board 1
		std::cout << "Jugador 1: " << std::endl;
		for (int i = 0; i < BOARD_SIZE; i++) {
			std::cout << i; //type casting
			std::cout << ' ';
		}
		std::cout << std::endl;
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				std::cout << visibleBoardPlayer1[i][j] << ' ';
			}
			std::cout << i;
			std::cout << '\n';
		}
		std::cout << "----------------------\n";
		std::cout << std::endl;

		// print board 2
		std::cout << "Jugador 2: " << std::endl;
		for (int i = 0; i < BOARD_SIZE; i++) {
			std::cout << i; //type casting
			std::cout << ' ';
		}
		std::cout << std::endl;
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				std::cout << visibleBoardPlayer2[i][j] << ' ';
			}
			std::cout << i;
			std::cout << '\n';
		}
		std::cout << "----------------------\n";


		//============ Input Handeling ========================================
		char inputs[50];
		int inputColomn = 0;
		int inputRow = 0;
		bool validInput = false;

		while (!validInput) {
			std::cout << "Player " << currentPlayer << " enter row and column: ";
			if (std::cin >> inputs) {
				inputColomn = (int)inputs[0] - '0';
				inputRow = (int)inputs[1] - '0';

				if (inputColomn < 0 || inputColomn > BOARD_SIZE - 1 || inputRow < 0 || inputRow > BOARD_SIZE - 1) {
					std::cout << "Input out of bounds, try again" << std::endl;
					continue;
				}
				validInput = true;
			}
			else {
				std::cout << "Please enter two numbers separated by whitespace.\n";
			}
		}

		//=========== check if tile that is selected is a ship and shoot???
		std::cout << "You entered column " << inputColomn << " and row " << inputRow << ".\n";
		if (currentPlayer == 2) {
			switch (boardPlayer1[inputRow][inputColomn]) {
				case '3':
				case '4':
				case '5':
				case '6': {
					visibleBoardPlayer1[inputRow][inputColomn] = HIT_MARK;
					whenHitGiveAnotherTurn = !whenHitGiveAnotherTurn;
					break;
				}
				case WATER: {
					visibleBoardPlayer1[inputRow][inputColomn] = MISS_MARK;
					whenHitGiveAnotherTurn = false;
					break;
				}
				default: {
					if (visibleBoardPlayer1[inputRow][inputColomn] == HIT_MARK || visibleBoardPlayer1[inputRow][inputColomn] == MISS_MARK) {
						std::cout << "This spot was already choosen once" << std::endl;
						break;
					}
					break;
				}
			}
		}

		else if (currentPlayer == 1) {
			switch (boardPlayer2[inputRow][inputColomn]) {
				case '3':
				case '4':
				case '5':
				case '6': {
					visibleBoardPlayer2[inputRow][inputColomn] = HIT_MARK;
					whenHitGiveAnotherTurn = !whenHitGiveAnotherTurn;
					break;
				}
				case WATER: {
					visibleBoardPlayer2[inputRow][inputColomn] = MISS_MARK;
					whenHitGiveAnotherTurn = false;
					break;
				}
				default: {
					if (visibleBoardPlayer2[inputRow][inputColomn] == HIT_MARK || visibleBoardPlayer2[inputRow][inputColomn] == MISS_MARK) {
						std::cout << "This spot was already choosen once" << std::endl;
						break;
					}
					break;
				}
			}
		}

		// ======== check how many ships are alive or not
		int remainingShipsPlayer1 = 0;
		int remainingShipsPlayer2 = 0;

		for (int s = 0; s < SHIP_COUNT; ++s) {
			bool alive1 = false, alive2 = false;

			for (int i = 0; i < BOARD_SIZE && !(alive1 && alive2); ++i) {
				for (int j = 0; j < BOARD_SIZE && !(alive1 && alive2); ++j) {
					if (boardPlayer1[i][j] == shipSymbols[s]) alive1 = true;
					if (boardPlayer2[i][j] == shipSymbols[s]) alive2 = true;
				}
			}

			if (alive1) ++remainingShipsPlayer1;
			if (alive2) ++remainingShipsPlayer2;
			if (!alive1 && !alive2) {
				std::cout << "Player " << currentPlayer << " destroyed ship " << shipSymbols[s] << "!\n";
			}
		}

		//================ win if there are no remaaining ships
		if (remainingShipsPlayer1 == 0) {
			gameOver = true;
			std::cout << "\n*** Player 2 wins! ***\n";
			break;
		}
		if (remainingShipsPlayer2 == 0) {
			gameOver = true;
			std::cout << "\n*** Player 1 wins! ***\n";
			break;
		}
	}

	return 0;
}
