#pragma once
struct Cell {
    char symbol;
    char shipAmount;
    bool hasShip;
    bool isHit;

    void Hit() { isHit = true; }
    bool Reveal() {
        if (hasShip) {
            symbol = shipAmount;
        }
        else {
            symbol = '~';
        }
    }
};