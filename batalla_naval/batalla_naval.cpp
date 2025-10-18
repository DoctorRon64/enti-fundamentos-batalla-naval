/*****************************************************************************************
 *  Battleship – Console version (C++20)
 *
 *  Author          : Philip de Groot
 *  Date created    : 2025‑10‑18
 *  Description     : Two‑player console Battleship game.  Boards are 10×10, ships of
 *                    lengths 3, 4, 5 and 6 are placed randomly.  Players alternate
 *                    entering row/column coordinates; hits are marked with 'O',
 *                    misses with 'X'.  The first player to sink all opponent ships
 *                    wins.
 *****************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>

int main() {
	std::cout << "Welcome to Battle Ship!" << std::endl;
	std::cout << "================================" << std::endl;
	std::cout << std::endl;

	const int BOARD_SIZE = 10;
	const int SHIP_COUNT = 4;
	const char WATER_CELL = '~';
	const char HIT_MARK = 'O';
	const char MISS_MARK = 'X';
	const int MAX_PLACEMENT_ATTEMPTS = 10000;

	char hiddenBoardP1[BOARD_SIZE][BOARD_SIZE];
	char hiddenBoardP2[BOARD_SIZE][BOARD_SIZE];
	char viewBoardP1[BOARD_SIZE][BOARD_SIZE];
	char viewBoardP2[BOARD_SIZE][BOARD_SIZE];

	//--------========= Initialize boards =========--------
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			hiddenBoardP1[i][j] = WATER_CELL;
			hiddenBoardP2[i][j] = WATER_CELL;
			viewBoardP1[i][j] = WATER_CELL;
			viewBoardP2[i][j] = WATER_CELL;
		}
	}

	//--------========= Randomly place ships for both players =========--------
	std::srand((unsigned int)std::time(0));
	int shipSizes[SHIP_COUNT] = { 3, 4, 5, 6 };

	char shipChars[SHIP_COUNT];
	for (int i = 0; i < SHIP_COUNT; ++i) {
		shipChars[i] = '0' + shipSizes[i];
	}

	//--------========= Place Ships for Player 1 =========--------
	for (int i = 0; i < 4; i++) {
		int currentShipSize = shipSizes[i];
		bool placed = false;
		int attempts = 0;

		while (!placed && attempts < 9999) {
			attempts++;

			int orientation = std::rand() % 2;
			int row = 0;
			int col = 0;
			if (orientation == 0) {
				row = std::rand() % BOARD_SIZE;
				col = std::rand() % (BOARD_SIZE - currentShipSize + 1);
			}
			else {
				row = std::rand() % (BOARD_SIZE - currentShipSize + 1);
				col = std::rand() % BOARD_SIZE;
			}

			bool canPlace = true;
			for (int j = 0; j < currentShipSize; j++) {
				int r = (orientation == 1) ? row + j : row;
				int c = (orientation == 1) ? col : col + j;

				if (hiddenBoardP1[r][c] != WATER_CELL) {
					canPlace = false;
					break;
				}
			}

			if (canPlace) {
				for (int j = 0; j < currentShipSize; j++) {
					int r = (orientation == 1) ? row + j : row;
					int c = (orientation == 1) ? col : col + j;
					hiddenBoardP1[r][c] = shipChars[i];
				}
				placed = true;
			}
		}
	}

	//--------========= Place Ships for Player 2 =========--------
	for (int i = 0; i < 4; i++) {
		int currentShipSize = shipSizes[i];
		bool placed = false;
		int attempts = 0;

		while (!placed && attempts < MAX_PLACEMENT_ATTEMPTS) {
			attempts++;

			int orientation = std::rand() % 2;
			int row = 0;
			int col = 0;
			if (orientation == 0) {
				row = std::rand() % BOARD_SIZE;
				col = std::rand() % (BOARD_SIZE - currentShipSize + 1);
			}
			else {
				row = std::rand() % (BOARD_SIZE - currentShipSize + 1);
				col = std::rand() % BOARD_SIZE;
			}

			bool canPlace = true;
			for (int j = 0; j < currentShipSize; j++) {
				int r = (orientation == 1) ? row + j : row;
				int c = (orientation == 1) ? col : col + j;

				if (hiddenBoardP2[r][c] != WATER_CELL) {
					canPlace = false;
					break;
				}
			}

			if (canPlace) {
				for (int j = 0; j < currentShipSize; j++) {
					int r = (orientation == 1) ? row + j : row;
					int c = (orientation == 1) ? col : col + j;
					hiddenBoardP2[r][c] = shipChars[i];
				}
				placed = true;
			}
		}
	}

	bool gameOver = false;
	int currentPlayer = 1;
	bool extraTurnOnHit = false;

	//--------========= Show full board (including ships) for Player 1 =========--------
	std::cout << "Player 1: " << std::endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		std::cout << i;
		std::cout << ' ';
	}
	std::cout << std::endl;
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			std::cout << hiddenBoardP1[i][j] << ' ';
		}
		std::cout << i;
		std::cout << '\n';
	}
	std::cout << "----------------------\n";
	std::cout << std::endl;

	std::cout << "Press Enter to clear the board.";
	std::string pauseLine;
	std::getline(std::cin, pauseLine);
	system("cls");
	std::cout << "Press Enter to continue.";
	std::getline(std::cin, pauseLine);
	std::cout << std::endl;

	//--------========= Show full board (including ships) for Player 2 =========--------
	std::cout << "Player 2: " << std::endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		std::cout << i;
		std::cout << ' ';
	}
	std::cout << std::endl;
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			std::cout << hiddenBoardP2[i][j] << ' ';
		}
		std::cout << i;
		std::cout << '\n';
	}
	std::cout << "----------------------\n";
	std::cout << std::endl;
	std::cout << "Press Enter to start the game.";
	std::getline(std::cin, pauseLine);

	while (!gameOver) {
		system("cls");
		if (!extraTurnOnHit) {
			currentPlayer = (currentPlayer % 2) + 1;
		}
		else {
			extraTurnOnHit = false;
		}

		//--------========= Print Boards =========--------
		std::cout << "Player 1: " << std::endl;
		for (int i = 0; i < BOARD_SIZE; i++) {
			std::cout << i;
			std::cout << ' ';
		}
		std::cout << std::endl;
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				std::cout << viewBoardP1[i][j] << ' ';
			}
			std::cout << i;
			std::cout << '\n';
		}
		std::cout << "----------------------\n";
		std::cout << std::endl;

		std::cout << "Player 2: " << std::endl;
		for (int i = 0; i < BOARD_SIZE; i++) {
			std::cout << i;
			std::cout << ' ';
		}
		std::cout << std::endl;
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				std::cout << viewBoardP2[i][j] << ' ';
			}
			std::cout << i;
			std::cout << '\n';
		}
		std::cout << "----------------------\n";

		//--------========= Input Handling =========--------
		char rawCoords[2];
		int inputColumn = 0;
		int inputRow = 0;
		bool validInput = false;

		while (!validInput) {
			std::cout << "Player " << currentPlayer << " – enter row and column (0‑9): ";

			if (std::cin >> rawCoords) {
				inputColumn = (int)rawCoords[0] - '0';
				inputRow = (int)rawCoords[1] - '0';

				if (inputColumn < 0 || inputColumn > BOARD_SIZE - 1 || inputRow < 0 || inputRow > BOARD_SIZE - 1) {
					std::cout << "Input out of bounds. INVALID. Pleas try again" << std::endl;
					continue;
				}
				validInput = true;
			}
			else {
				std::cout << "Please enter two numbers\n";
			}
		}

		//--------========= Resolve shot and update boards =========--------
		std::cout << "You entered column " << inputColumn << " and row " << inputRow << ".\n";
		if (currentPlayer == 2) {
			switch (hiddenBoardP1[inputRow][inputColumn]) {
				case '3':
				case '4':
				case '5':
				case '6': {
					if (viewBoardP1[inputRow][inputColumn] != WATER_CELL) {
						std::cout << "That square was already chosen. Pick another.\n";
						continue;
					}
					viewBoardP1[inputRow][inputColumn] = HIT_MARK;
					hiddenBoardP1[inputRow][inputColumn] = HIT_MARK;
					
					extraTurnOnHit = true;
					break;
				}
				case WATER_CELL: {
					if (viewBoardP2[inputRow][inputColumn] != WATER_CELL) {
						std::cout << "That square was already chosen. Pick another.\n";
						continue;
					}

					viewBoardP1[inputRow][inputColumn] = MISS_MARK;
					extraTurnOnHit = false;
					break;
				}
				default: {
					if (viewBoardP1[inputRow][inputColumn] == HIT_MARK || viewBoardP1[inputRow][inputColumn] == MISS_MARK) {
						std::cout << "This spot was already choosen once" << std::endl;
						break;
					}
					break;
				}
			}
		}

		else if (currentPlayer == 1) {
			switch (hiddenBoardP2[inputRow][inputColumn]) {
				case '3':
				case '4':
				case '5':
				case '6': {
					if (viewBoardP2[inputRow][inputColumn] != WATER_CELL) {
						std::cout << "That square was already chosen. Pick another.\n";
						continue;
					}
					viewBoardP2[inputRow][inputColumn] = HIT_MARK;
					hiddenBoardP2[inputRow][inputColumn] = HIT_MARK;
					
					extraTurnOnHit = true;
					break;
				}
				case WATER_CELL: {
					if (viewBoardP2[inputRow][inputColumn] != WATER_CELL) {
						std::cout << "That square was already chosen. Pick another.\n";
						continue;
					}

					viewBoardP2[inputRow][inputColumn] = MISS_MARK;
					extraTurnOnHit = false;
					break;
				}
				default: {
					if (viewBoardP2[inputRow][inputColumn] == HIT_MARK || viewBoardP2[inputRow][inputColumn] == MISS_MARK) {
						std::cout << "This spot was already choosen once" << std::endl;
						break;
					}
					break;
				}
			}
		}

		//--------========= Count remaining ships for each player =========--------
		int p1ShipsAlive = 0;
		int p2ShipsAlive = 0;

		for (int shipIdx = 0; shipIdx < SHIP_COUNT; ++shipIdx) {
			bool p1Alive = false, p2Alive = false;

			for (int i = 0; i < BOARD_SIZE && !(p1Alive && p2Alive); ++i) {
				for (int j = 0; j < BOARD_SIZE && !(p1Alive && p2Alive); ++j) {
					if (hiddenBoardP1[i][j] == shipChars[shipIdx]) p1Alive = true;
					if (hiddenBoardP2[i][j] == shipChars[shipIdx]) p2Alive = true;
				}
			}

			if (p1Alive) ++p1ShipsAlive;
			if (p2Alive) ++p2ShipsAlive;
			if (!p1Alive && !p2Alive) {
				std::cout << "Player " << currentPlayer << " destroyed ship " << shipChars[shipIdx] << "!\n";
			}
		}

		//--------========= Win and Lose condition =========--------
		if (p1ShipsAlive == 0) {
			gameOver = true;
			std::cout << "\n*** Player 2 wins! ***\n";
			break;
		}
		if (p2ShipsAlive == 0) {
			gameOver = true;
			std::cout << "\n*** Player 1 wins! ***\n";
			break;
		}
	}

	return 0;
}
