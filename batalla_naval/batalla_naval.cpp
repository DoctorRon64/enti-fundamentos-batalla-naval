#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>

int main() {
	std::cout << "=================================================\n";
	std::cout << "------------Welcome to Battle Ship!--------------\n";
	std::cout << "=================================================\n\n";

	const short BOARD_SIZE = 10;
	const char WATER_CELL = '~';
	const char HIT_MARK = 'O';
	const char MISS_MARK = 'X';

	const short FIRST_SHIP = 6;
	const short LAST_SHIP = 3;
	const short MAX_PLACEMENT_ATTEMPTS = 9999;
	const short MAX_IGNORE_INPUT = 1000;

	const short P1_INDEX = 1;
	const short P2_INDEX = 2;

	char hiddenBoardP1[BOARD_SIZE][BOARD_SIZE];
	char hiddenBoardP2[BOARD_SIZE][BOARD_SIZE];
	char viewBoardP1[BOARD_SIZE][BOARD_SIZE];
	char viewBoardP2[BOARD_SIZE][BOARD_SIZE];

	bool grantExtraTurn = false;
	bool stayOnTurn = false;
	short currentPlayer = 0;

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// -------- Initialize boards --------
	for(short i = 0; i < BOARD_SIZE; ++i) {
		for(short j = 0; j < BOARD_SIZE; ++j) {
			hiddenBoardP1[i][j] = WATER_CELL;
			hiddenBoardP2[i][j] = WATER_CELL;
			viewBoardP1[i][j] = WATER_CELL;
			viewBoardP2[i][j] = WATER_CELL;
		}
	}

	// -------- Place ships --------
	for(short player = P1_INDEX; player <= P2_INDEX; ++player) {
		for(short shipSize = FIRST_SHIP; shipSize >= LAST_SHIP; --shipSize) {
			bool placed = false;
			short attempts = 0;
			char shipChar = '0' + shipSize;

			while(!placed && attempts < MAX_PLACEMENT_ATTEMPTS) {
				++attempts;

				short orientation = std::rand() % 2;
				short row, col;

				if(orientation == 0) {
					row = std::rand() % BOARD_SIZE;
					col = std::rand() % (BOARD_SIZE - shipSize + 1);
				}
				else {
					row = std::rand() % (BOARD_SIZE - shipSize + 1);
					col = std::rand() % BOARD_SIZE;
				}

				bool canPlace = true;

				for(short i = 0; i < shipSize; ++i) {
					short r = row + (orientation == 1 ? i : 0);
					short c = col + (orientation == 0 ? i : 0);

					if(player == 1 && hiddenBoardP1[r][c] != WATER_CELL) {
						canPlace = false;
					}
					if(player == 2 && hiddenBoardP2[r][c] != WATER_CELL) {
						canPlace = false;
					}
				}

				if(canPlace) {
					for(short i = 0; i < shipSize; ++i) {
						short r = row + (orientation == 1 ? i : 0);
						short c = col + (orientation == 0 ? i : 0);

						if(player == 1)
							hiddenBoardP1[r][c] = shipChar;
						else
							hiddenBoardP2[r][c] = shipChar;
					}
					placed = true;
				}
			}

			if(!placed) {
				std::cout << "ERROR: Could not place ship size " << shipSize << "\n";
				return 1;
			}
		}

		// -------- Show each player their own ships --------
		system("cls");
		std::cout << "Player " << player << ", here are your ships:\n\n";

		for(short i = 1; i <= BOARD_SIZE; ++i) {
			std::cout << i << ' ';
		}
		std::cout << '\n';

		for(short i = 0; i < BOARD_SIZE; ++i) {
			for(short j = 0; j < BOARD_SIZE; ++j) {
				if(player == 1) {
					std::cout << hiddenBoardP1[i][j] << ' ';
				}
				else {
					std::cout << hiddenBoardP2[i][j] << ' ';
				}
			}
			std::cout << i + 1 << '\n';
		}

		std::cout << "\nPress Enter when ready...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::cout << std::endl;
	std::cout << "Press Enter to start the game.";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// -------- Game loop --------
	while(true) {
		system("cls");

		if(!grantExtraTurn && !stayOnTurn) {
			currentPlayer = (currentPlayer % 2) + 1;
		}

		grantExtraTurn = false;
		stayOnTurn = false;

		// -------- Print view boards --------
		for(short p = P1_INDEX; p <= P2_INDEX; ++p) {
			std::cout << "Player " << p << ":\n";

			for(short i = 1; i <= BOARD_SIZE; ++i) {
				std::cout << i << ' ';
			}
			std::cout << '\n';

			for(short i = 0; i < BOARD_SIZE; ++i) {
				for(short j = 0; j < BOARD_SIZE; ++j) {
					if(p == 1) {
						std::cout << viewBoardP1[i][j] << ' ';
					}
					else {
						std::cout << viewBoardP2[i][j] << ' ';
					}
				}
				std::cout << i + 1 << '\n';
			}
			std::cout << "----------------------\n\n";
		}

		// -------- Input --------
		short row = 0;
		short col = 0;
		bool validInput = false;

		while(!validInput) {
			bool inputOk = true;

			std::cout << "Player " << currentPlayer << ", enter column [1-10]: ";
			std::cin >> col;

			if(std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(MAX_IGNORE_INPUT, '\n');
				std::cout << "Invalid input. Numbers only.\n";
				inputOk = false;
			}

			if(inputOk) {
				std::cout << "Enter row [1-10]: ";
				std::cin >> row;

				if(std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(MAX_IGNORE_INPUT, '\n');
					std::cout << "Invalid input. Numbers only.\n";
					inputOk = false;
				}
			}

			if(inputOk) {
				if(col <= 0 || col > BOARD_SIZE || row <= 0 || row > BOARD_SIZE) {
					std::cout << "Out of bounds. Use 1 to 10.\n";
					inputOk = false;
				}
			}

			validInput = inputOk;
		}

		short r = row - 1;
		short c = col - 1;

		// -------- Resolve shot --------
		char (*targetHidden)[BOARD_SIZE] = (currentPlayer == P1_INDEX) ? hiddenBoardP2 : hiddenBoardP1;
		char (*targetView)[BOARD_SIZE] = (currentPlayer == P1_INDEX) ? viewBoardP2 : viewBoardP1;

		if(targetView[r][c] != WATER_CELL) {
			std::cout << "Already shot there!\n";
			stayOnTurn = true;
		}
		else {
			if(targetHidden[r][c] != WATER_CELL) {
				targetView[r][c] = HIT_MARK;
				targetHidden[r][c] = HIT_MARK;
				std::cout << "Hit!\n";
				grantExtraTurn = true;
			}
			else {
				targetView[r][c] = MISS_MARK;
				targetHidden[r][c] = MISS_MARK;
				std::cout << "Miss!\n";
			}
		}

		std::cout << "Press Enter to continue...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();

		// -------- Win check --------
		bool p1Alive = false;
		bool p2Alive = false;

		for(short i = 0; i < BOARD_SIZE; ++i) {
			for(short j = 0; j < BOARD_SIZE; ++j) {
				if(hiddenBoardP1[i][j] >= '3' && hiddenBoardP1[i][j] <= '6')
					p1Alive = true;
				if(hiddenBoardP2[i][j] >= '3' && hiddenBoardP2[i][j] <= '6')
					p2Alive = true;
			}
		}

		if(!p1Alive) {
			std::cout << "\n*** Player 2 wins! ***\n";
			break;
		}
		if(!p2Alive) {
			std::cout << "\n*** Player 1 wins! ***\n";
			break;
		}
	}

	return 0;
}