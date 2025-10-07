#include <iostream>
#include <vector>
#include <memory>
#include "Player.h"
#include "PlayerSelectorScreen.h"

PlayerSelectorScreen::PlayerSelectorScreen() {
    std::cout << "¿Con cuántos jugadores vas a jugar? (Solo 2, 3 o 4 jugadores pueden jugar): " << std::endl;
    uint32_t playerAmount = askPlayerAmount();

    for (uint32_t i = 0; i < playerAmount; i++) {
        //TODO
        //give each player a name 
        auto player = std::make_shared<Player>();
        players.push_back(player);
    }
}   

uint32_t PlayerSelectorScreen::askPlayerAmount() {
    uint32_t amount = 0;
    while (true) {
        std::cin >> amount;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Entrada no válida. Ingrese un número!\n";
            continue;
        }
        if (amount >= 2 && amount <= 4) return amount;
        std::cout << "Solo se permiten 2, 3 o 4 jugadores.\n";
    }
}

const std::vector<std::shared_ptr<Player>>& PlayerSelectorScreen::GetPlayers() const {
    return players;
}