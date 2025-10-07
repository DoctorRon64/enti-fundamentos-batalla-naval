#pragma once
#include <vector>
#include <memory>
#include "Player.h"

class PlayerSelectorScreen {
public:
	PlayerSelectorScreen();
	const std::vector<std::shared_ptr<Player>>& GetPlayers() const;
private:
	uint32_t askPlayerAmount();
	std::vector<std::shared_ptr<Player>> players;
};

