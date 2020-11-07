#ifndef Game_H
#define Game_H
#include "Snake.h"
#include "Screen.h"

class Food {
public:
    Food(int r = 0, int c = 0, int t = 0) : posX(c), posY(r), tempo(t) {}

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
    Game(int, int, int);
    Game(const Game&);
    ~Game();

    const Screen & getScreen();
    int getNumFood();

    bool step(int, int);

    void addFood(int, int, int);
    void foodDown();
    void drawFood();

    Game& operator= (const Game&);

private:
    Snake snake;
    Screen screen;
    Food food[10];
    int numFood = 0;
    int lastStepX = 1, lastStepY = 0;
};

#endif