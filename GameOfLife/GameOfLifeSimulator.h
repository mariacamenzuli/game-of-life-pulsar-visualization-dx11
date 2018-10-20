#pragma once

class GameOfLifeSimulator {
public:
    GameOfLifeSimulator();
    ~GameOfLifeSimulator();

    void update(float deltaTime);

private:
    enum class Cell {
        ALIVE, DEAD
    };

    Cell cells[10][3];
};
