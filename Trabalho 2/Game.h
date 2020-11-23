#ifndef Game_H
#define Game_H
#include "Snake.h"
#include "Screen.h"

class Food {
public:
    Food(int r = 0, int c = 0, int t = -1) : posX(c), posY(r), tempo(t) {}

    Food& operator=(const Food &other) {
        for (int i = 0; i < 10; i++) {
            this->posX = other.posX;
            this->posY = other.posY;
            this->tempo = other.tempo;
        }

        return *this;
    }

    int posX, posY, tempo;
;
};

class Game {
public:
    Game(int height, int width, int size);
    Game(const Game &other);
    ~Game();

    const Screen & getScreen();
    int getNumFood();

    bool step(int dr, int dc);

    void addFood(int r, int c, int ttl);

    Game& operator= (const Game &other);

private:
    Snake snake;
    Screen screen;
    Food food[10];
    int lastStepX = 1, lastStepY = 0;   // A cobra inicialmente se move para a direita

    void foodDown();
    void drawFood();
};

#endif