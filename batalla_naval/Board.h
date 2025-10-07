#pragma once
#include "Cell.h"
#include <iostream>
#include <vector>

constexpr int zak = 10;

class Board {
public:
	Board();

	void Display();
private:
	Cell grid[zak][zak];

};