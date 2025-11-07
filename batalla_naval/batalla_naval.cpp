#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>

int main() {
	std::cout << "=================================================" << std::endl;
	std::cout << "------------Welcome to Battle Ship!--------------" << std::endl;
	std::cout << "=================================================" << std::endl;
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

	bool gameOver = false;
	bool extraTurnOnHit = false;
	bool repeatTurn = false;
	int currentPlayer = 0;

	std::srand((unsigned int)std::time(0));
	int shipSizes[SHIP_COUNT] = { 3, 4, 5, 6 };

	//--------========= Initialize boards =========--------
	for(int i = 0; i < BOARD_SIZE; ++i) {
		for(int j = 0; j < BOARD_SIZE; ++j) {
			hiddenBoardP1[i][j] = WATER_CELL;
			hiddenBoardP2[i][j] = WATER_CELL;
			viewBoardP1[i][j] = WATER_CELL;
			viewBoardP2[i][j] = WATER_CELL;
		}
	}

	//--------========= Randomly place ships for both players =========--------
	char shipChars[SHIP_COUNT];
	for(int i = 0; i < SHIP_COUNT; ++i) {
		shipChars[i] = '0' + shipSizes[i];
	}

	//--------========= Place Ships for Player 1 =========--------
	for(int i = 0; i < 4; i++) {
		int currentShipSize = shipSizes[i];
		bool placed = false;
		int attempts = 0;

		while(!placed && attempts < 9999) {
			attempts++;

			int orientation = std::rand() % 2;
			int row = 0;
			int col = 0;
			if(orientation == 0) {
				row = std::rand() % BOARD_SIZE;
				col = std::rand() % (BOARD_SIZE - currentShipSize + 1);
			}
			else {
				row = std::rand() % (BOARD_SIZE - currentShipSize + 1);
				col = std::rand() % BOARD_SIZE;
			}

			bool canPlace = true;
			for(int j = 0; j < currentShipSize; j++) {
				int r = (orientation == 1) ? row + j : row;
				int c = (orientation == 1) ? col : col + j;

				if(hiddenBoardP1[r][c] != WATER_CELL) {
					canPlace = false;
					break;
				}
			}

			if(canPlace) {
				for(int j = 0; j < currentShipSize; j++) {
					int r = (orientation == 1) ? row + j : row;
					int c = (orientation == 1) ? col : col + j;
					hiddenBoardP1[r][c] = shipChars[i];
				}
				placed = true;
			}
		}
	}

	//--------========= Place Ships for Player 2 =========--------
	for(int i = 0; i < 4; i++) {
		int currentShipSize = shipSizes[i];
		bool placed = false;
		int attempts = 0;

		while(!placed && attempts < MAX_PLACEMENT_ATTEMPTS) {
			attempts++;

			int orientation = std::rand() % 2;
			int row = 0;
			int col = 0;
			if(orientation == 0) {
				row = std::rand() % BOARD_SIZE;
				col = std::rand() % (BOARD_SIZE - currentShipSize + 1);
			}
			else {
				row = std::rand() % (BOARD_SIZE - currentShipSize + 1);
				col = std::rand() % BOARD_SIZE;
			}

			bool canPlace = true;
			for(int j = 0; j < currentShipSize; j++) {
				int r = (orientation == 1) ? row + j : row;
				int c = (orientation == 1) ? col : col + j;

				if(hiddenBoardP2[r][c] != WATER_CELL) {
					canPlace = false;
					break;
				}
			}

			if(canPlace) {
				for(int j = 0; j < currentShipSize; j++) {
					int r = (orientation == 1) ? row + j : row;
					int c = (orientation == 1) ? col : col + j;
					hiddenBoardP2[r][c] = shipChars[i];
				}
				placed = true;
			}
		}
	}

	//--------========= Show full board (including ships) for Player 1 =========--------
	std::string pauseLine;
	std::cout << "Press Enter to show the board of Player 1." << std::endl;
	std::getline(std::cin, pauseLine);
	for(int i = 0; i < BOARD_SIZE; i++) {
		std::cout << i + 1;
		std::cout << ' ';
	}
	std::cout << std::endl;
	for(int i = 0; i < BOARD_SIZE; ++i) {
		for(int j = 0; j < BOARD_SIZE; ++j) {
			std::cout << hiddenBoardP1[i][j] << ' ';
		}
		std::cout << i + 1;
		std::cout << '\n';
	}
	std::cout << "----------------------\n";
	std::cout << std::endl;
	std::cout << "Press Enter to clear the board.";
	std::getline(std::cin, pauseLine);
	system("cls");
	std::cout << "Press Enter to show the board of Player 2.";
	std::getline(std::cin, pauseLine);
	std::cout << std::endl;

	//--------========= Show full board (including ships) for Player 2 =========--------
	for(int i = 0; i < BOARD_SIZE; i++) {
		std::cout << i + 1;
		std::cout << ' ';
	}
	std::cout << std::endl;
	for(int i = 0; i < BOARD_SIZE; ++i) {
		for(int j = 0; j < BOARD_SIZE; ++j) {
			std::cout << hiddenBoardP2[i][j] << ' ';
		}
		std::cout << i + 1;
		std::cout << '\n';
	}
	std::cout << "----------------------\n";
	std::cout << std::endl;
	std::cout << "Press Enter to start the game.";
	std::getline(std::cin, pauseLine);

	while(!gameOver) {
		system("cls");
		if(!extraTurnOnHit && !repeatTurn) {
			currentPlayer = (currentPlayer % 2) + 1;
		}
		repeatTurn = false;

		//--------========= Print Boards =========--------
		std::cout << "Player 1: " << std::endl;
		for(int i = 0; i < BOARD_SIZE; i++) {
			std::cout << i + 1;
			std::cout << ' ';
		}
		std::cout << std::endl;
		for(int i = 0; i < BOARD_SIZE; ++i) {
			for(int j = 0; j < BOARD_SIZE; ++j) {
				std::cout << viewBoardP1[i][j] << ' ';
			}
			std::cout << i + 1;
			std::cout << '\n';
		}
		std::cout << "----------------------\n";
		std::cout << std::endl;

		std::cout << "Player 2: " << std::endl;
		for(int i = 0; i < BOARD_SIZE; i++) {
			std::cout << i + 1;
			std::cout << ' ';
		}
		std::cout << std::endl;
		for(int i = 0; i < BOARD_SIZE; ++i) {
			for(int j = 0; j < BOARD_SIZE; ++j) {
				std::cout << viewBoardP2[i][j] << ' ';
			}
			std::cout << i + 1;
			std::cout << '\n';
		}
		std::cout << "----------------------\n";
		std::cout << std::endl;

		//--------========= Input Handling =========--------
		char rawInput[5];
		int inputColomn[2];
		int inputRow[2];
		int Row;
		int Column;
		bool validInput = false;

		while(!validInput) {
			std::cout << "Player " << currentPlayer;
			if(extraTurnOnHit) std::cout << " EXTRA";
			std::cout << " turn, ";

			std::cout << "enter column [1/10]: ";
			if(std::cin >> rawInput) {
				inputColomn[0] = rawInput[0] - '0';
				inputColomn[1] = rawInput[1] - '0';

				if(inputColomn[0] < 1 || inputColomn[0] > 10) {
					std::cout << "Input out of bounds. Please enter a number between 1 and 10." << std::endl;
					continue;
				}

				if(inputColomn[0] == 1 && inputColomn[1] == 0) {
					Column = 9;
					std::cout << "You entered column 10, ";
				}
				else {
					Column = inputColomn[0] - 1;
					std::cout << "You entered column " << inputColomn[0] << ", ";
				}
			}
			else {
				std::cout << "Invalid input. Please enter a number." << std::endl;
				continue;
			}

			std::cout << "Enter row [1/10]: ";
			if(std::cin >> rawInput) {
				inputRow[0] = rawInput[0] - '0';
				inputRow[1] = rawInput[1] - '0';

				if(inputRow[0] < 1 || inputRow[0] > 10) {
					std::cout << "Input out of bounds. Please enter a number between 1 and 10." << std::endl;
					continue;
				}

				if(inputRow[0] == 1 && inputRow[1] == 0) {
					Row = 9;
					std::cout << "You entered row 10" << std::endl;
					validInput = true;
				}
				else {
					Row = inputRow[0] - 1;
					std::cout << "You entered row " << inputRow[0] << std::endl;
					validInput = true;
				}
			}
			else {
				std::cout << "Invalid input. Please enter a number." << std::endl;
				continue;
			}
		}

		if(extraTurnOnHit) {
			extraTurnOnHit = false;
		}

		//--------========= Resolve shot and update boards =========--------
		std::cout << "You entered column " << Column << " and row " << Row << ".\n";
		if(currentPlayer == 1) {
			char target = hiddenBoardP2[Row][Column];
			if(viewBoardP2[Row][Column] == WATER_CELL) {
				if(target != WATER_CELL) {
					viewBoardP2[Row][Column] = HIT_MARK;
					hiddenBoardP2[Row][Column] = HIT_MARK;
					std::cout << "Hit!" << std::endl;
					extraTurnOnHit = true;
				}
				else {
					viewBoardP2[Row][Column] = MISS_MARK;
					hiddenBoardP2[Row][Column] = MISS_MARK;
					std::cout << "Miss!" << std::endl;
					extraTurnOnHit = false;
				}
			}
			else {
				std::cout << "You already shot there! Pick another." << std::endl;
				repeatTurn = true;
			}
		}
		else if(currentPlayer == 2) {
			char target = hiddenBoardP1[Row][Column];
			if(viewBoardP1[Row][Column] == WATER_CELL) {
				if(target != WATER_CELL) {
					viewBoardP1[Row][Column] = HIT_MARK;
					hiddenBoardP1[Row][Column] = HIT_MARK;
					std::cout << "Hit!" << std::endl;
					extraTurnOnHit = true;
				}
				else {
					viewBoardP1[Row][Column] = MISS_MARK;
					hiddenBoardP1[Row][Column] = MISS_MARK;
					std::cout << "Miss!" << std::endl;
					extraTurnOnHit = false;
				}
			}
			else {
				std::cout << "You already shot there! Pick another." << std::endl;
				repeatTurn = true;
			}
		}

		//--------========= Count remaining ships for each player =========--------
		int p1ShipsAlive = 0;
		int p2ShipsAlive = 0;

		for(int shipIdx = 0; shipIdx < SHIP_COUNT; ++shipIdx) {
			bool p1Alive = false, p2Alive = false;

			for(int i = 0; i < BOARD_SIZE && !(p1Alive && p2Alive); ++i) {
				for(int j = 0; j < BOARD_SIZE && !(p1Alive && p2Alive); ++j) {
					if(hiddenBoardP1[i][j] == shipChars[shipIdx]) p1Alive = true;
					if(hiddenBoardP2[i][j] == shipChars[shipIdx]) p2Alive = true;
				}
			}

			if(p1Alive) ++p1ShipsAlive;
			if(p2Alive) ++p2ShipsAlive;
			if(!p1Alive && !p2Alive) {
				std::cout << "Player " << currentPlayer << " destroyed ship " << shipChars[shipIdx] << "!\n";
			}
		}

		//--------========= Win and Lose condition =========--------
		if(p1ShipsAlive == 0) {
			gameOver = true;
			std::cout << "\n*** Player 2 wins! ***\n";
			break;
		}
		if(p2ShipsAlive == 0) {
			gameOver = true;
			std::cout << "\n*** Player 1 wins! ***\n";
			break;
		}
	}

	return 0;
}