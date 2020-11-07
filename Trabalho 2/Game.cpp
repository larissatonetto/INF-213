#include "Game.h"
#include <iostream>

Game::Game(int height, int width, int size) {
    screen = Screen(height, width);
    snake = new Snake(size);
    snake->draw(*screen,1);
    // drawFood();
}

Game::Game(const Game &other) {
    std::cout << "Construtor de cópia\n";
    // snake->create();
    // screen->create();

    /*for (int i = 0; i < 10; i++) {
        food[i] = other.food[i];
    }

    screen = other.screen;
    snake = other.snake;*/

    *this = other;
}

Game::~Game() {
    screen->destroy();
    snake->destroy();
    // delete[] screen;
    // delete[] snake;
    // delete[] this;
}

Game& Game::operator= (const Game &other) {
    std::cout << "Operador de atribuição\n";
    snake->destroy();
    screen->destroy();

    for (int i = 0; i < 10; i++) {
        food[i] = other.food[i];
    }
    
    // Alocando screen:
    *screen = *other.screen;
    *snake = *other.snake;

    return *this;
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
    snake->draw(*screen,1);
    foodDown();
    drawFood();
    // lastStep é responsável pelo movimento
    // Verificar se lastStep deve ser atualizado (não houve inversão de direção)
    if ((dr != 0) && (lastStepY != (dr*-1) || lastStepY == 0)) {
        lastStepY = dr;
        lastStepX = dc;
    } else if ((dc != 0) && (lastStepX != (dc*-1) || lastStepX == 0)) {
        lastStepY = dr;
        lastStepX = dc;
    }

    // snake->draw(*screen,1);

    if (snake->head('y')+lastStepY == screen->getHeight() ||
        snake->head('x')+lastStepX == screen->getWidth() ||
        snake->head('y')+lastStepY < 0 ||
        snake->head('x')+lastStepX < 0) {
        snake->draw(*screen,1);
        return false;
    }

    if (screen->get(( snake->head('y')+lastStepY ), ( snake->head('x')+lastStepX )) == 1) {
        snake->draw(*screen,1);
        return false;
    }
    // snake->draw(*screen,1);
    snake->draw(*screen,0);

    // Se há comida no espaço
    if (screen->get(( snake->head('y')+lastStepY ), ( snake->head('x')+lastStepX )) == 2) {
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
    if (screen->get(r,c) == 1) return;
    // Encontra o primeiro espaço disponível no array de food para armazenar
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
    // Diminui o tempo de vida de todas as comidas no array
    for (int i = 0; i < 10; i++) {
        food[i].tempo-= 1;
        // if (food[i].tempo < 0) screen->set((food[i].posY),(food[i].posX),0);
        // else screen->set((food[i].posY),(food[i].posX),2);
    }
}

void Game::drawFood() {
    for (int i = 0; i < 10; i++) {
        if (food[i].tempo >= 0) {
            if (screen->get(food[i].posY,food[i].posX) != 1)
                screen->set(food[i].posY,food[i].posX,2);
        }
        else if (food[i].tempo < 0)
            if (screen->get(food[i].posY,food[i].posX) != 1)
                screen->set(food[i].posY,food[i].posX,0);
    }
}