#pragma once
class Cell {
public:
    
    void Hit();
    void Reveal();


private:
    char symbol; //~ X O 4521
    bool hasShip;
    bool isHit;
};

