#ifndef Game_H
#define Game_H
#include "Snake.h"
#include "Screen.h"

class Food {
public:
    Food(int r = 0, int c = 0, int t = 0) : posX(c), posY(r), tempo(t) {}

private:
    int posX, posY, tempo;
};

class Game {
public:
    Game(int, int, int);
    ~Game();

    Screen getScreen();
    int getNumFood();

    bool step(int, int);

    void addFood(int, int, int);

private:
    Snake *snake;
    Screen *screen;
    Food food[10];
    int numFood = 0;
    int lastStepX = -2, lastStepY = -2;
};

// Se o tempo de vida é 0, pode sersubstituído
// addFood usa screen.set dentro do método

#endif