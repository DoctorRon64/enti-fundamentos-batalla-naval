#pragma once
#include "Board.h"

class Player {
public:
	Player();

	std::shared_ptr<Board> GetBoard();
private:
	std::shared_ptr<Board> board;
};

