#include "Player.h"
#include "PlayerSelectorScreen.h"
#include <iostream>
#include <memory>
#include <vector>

int main() {
    bool gameRunning = true;

    std::cout << "Bienvenido a Batalla naval!" << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << std::endl;

    std::shared_ptr<PlayerSelectorScreen> playerSelectorScreen = std::make_shared<PlayerSelectorScreen>();
    std::vector<std::shared_ptr<Player>> players = playerSelectorScreen->GetPlayers();

    std::cout << "Número de jugadores: " << players.size() << std::endl;

    /*while (gameRunning) {
        for (int i = 0; i < players.size(); i++) {
            // turn logic here
        }
    }*/
}
