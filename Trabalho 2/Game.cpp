#include "Game.h"
#include <iostream>

Game::Game(int height, int width, int size) {
    screen = new Screen(height, width);
    snake = new Snake(size);
    snake->draw(*screen,1);
}

Game::~Game() {
    screen->destroy();
    snake->destroy();
}

const Screen & Game::getScreen() {
    return *screen;
}

int Game::getNumFood() {
    int cont = 0;
    for (int i = 0; i < 10; i++) {
        if (food[i].tempo != 0) cont++;
    }

    return cont;
}

bool Game::step(int dr, int dc) {
    // lastStep é responsável pelo movimento
    // Verificar se lastStep deve ser atualizado
    if ((lastStepY != (dr*-1) || lastStepY == 0) || (lastStepX != (dc*-1) || lastStepX == 0)) {
        lastStepY = dr;
        lastStepX = dc;
    }

    // A cobra é desenhada no início de step() para que possa verificar
    // se houve colisão com ela mesma
    snake->draw(*screen,1);
    if (screen->get(( snake->head('y')+lastStepY ), ( snake->head('x')+lastStepX )) == 1) {
            return false;
    }

    snake->draw(*screen,0);
    foodDown();
    // Se vai bater na parede
    if (snake->head('y')+lastStepY == screen->getHeight() ||
            snake->head('x')+lastStepX == screen->getWidth() ||
        snake->head('y')+lastStepY < 0 ||
        snake->head('x')+lastStepX < 0) {
        return false;
    // Se há comida no espaço
    } else if (screen->get(( snake->head('y')+lastStepY ), ( snake->head('x')+lastStepX )) == 2) {
        snake->move(lastStepY,lastStepX,true);
        snake->draw(*screen,1);
        return true;
    } else {
        snake->move(lastStepY,lastStepX,false);
        snake->draw(*screen,1);
        return true;
    }

    return true;
}

void Game::addFood(int r, int c, int t) {
    // Se chegar o limite de tempo, setar para 0 novamente
    for (int i = 0; i < 10; i++) {
        if (food[i].tempo <= 0) {
            food[i].posY = r;
            food[i].posX = c;
            food[i].tempo = t;

            break;
        }
    }
    screen->set(r,c,2);
}

void Game::foodDown() {
    for (int i = 0; i < 10; i++) {
        food[i].tempo-= 1;
        if (food[i].tempo < 0) screen->set((food[i].posY),(food[i].posX),0);
    }
}