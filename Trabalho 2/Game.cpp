#include "Game.h"
#include <iostream>

Game::Game(int height, int width, int size) {
    screen = new Screen(height, width);
    snake = new Snake(size);
}

Game::~Game() {
    screen->destroy();
    snake->destroy();
}

Screen Game::getScreen() {
    return *screen;         // ??????????
}

bool Game::step(int dr, int dc) {
    if (lastStepY == (dr*-1) && lastStepY != 0) {
    } else if (lastStepX == (dc*-1) && lastStepX != 0) {
    } else {
        // Se vai bater na parede
        if (snake->head('y')+dr == screen->getHeight() ||
            snake->head('x')+dc == screen->getWidth() ||
            snake->head('y')+dr < 0 ||
            snake->head('x')+dc < 0) {
            return false;
        // Se há comida no espaço
        } else if (screen->get(( snake->head('y')+dr ), ( snake->head('x')+dc )) == 2) {
            lastStepY = dr;
            lastStepX = dc;
            snake->move(dr,dc,true);
            return true;
        // Se vai bater nela mesma
        } else if (screen->get(( snake->head('y')+dr ), ( snake->head('x')+dc ) == 1)) {
            return false;
        } else {
            lastStepY = dr;
            lastStepX = dc;
            snake->move(dr,dc,false);
            return true;
        }
    }

    /*if (lastStepY == (dr*-1)) {
        std::cout << "Movimento inválido Y\n";
        std::cout << "lastY = " << lastStepY<< "\n";
        std::cout << "dr = " << dr << "\n";
    } else if (lastStepX == (dc*-1)) {
        std::cout << "Movimento inválido X\n";
        std::cout << "lastX = " << lastStepX << "\n";
        std::cout << "dc = " << dc << "\n";
    }

    else {
        snake->move(dr,dc,true);
        lastStepY = dr;
        lastStepX = dc;
    }*/

    return true;
}