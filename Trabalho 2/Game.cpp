#include "Game.h"
#include <iostream>

Game::Game(int height, int width, int size) {
    screen = new Screen(height, width);
    snake = new Snake(size);
    // screen->set(0,0,1);
    // snake->draw(screen,1);
}

Game::~Game() {
    screen->destroy();
    snake->destroy();
}

const Screen & Game::getScreen() {
    return *screen;         // ??????????
}

int Game::getNumFood() {
    int cont = 0;
    for (int i = 0; i < 10; i++) {
        if (food[i].tempo != 0) cont++;
    }

    return cont;
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
            snake->draw(screen,1);
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

    return true;
}

void Game::addFood(int r, int c, int t) {

}