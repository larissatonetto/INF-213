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
    if (lastStepY == (dr*-1) && lastStepY != 0) { std::cout << "Inválido\n";
    } else if (lastStepX == (dc*-1) && lastStepX != 0) {    std::cout << "Inválido\n";
    } else {
        lastStepY = dr;
        lastStepX = dc;
        if (screen->get(( snake->head('y')+dr ), ( snake->head('x')+dc )) == 2) {
            snake->move(dr,dc,true);
            return true;
        } else if (screen->get(( snake->head('y')+dr ), ( snake->head('x')+dc ) == 1 || 3)) {
            std::cout << "Bateu\n";
            return false;
        } else {
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