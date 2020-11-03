#include "Game.h"
#include <iostream>

Game::Game(int height, int width, int size) {
    screen = new Screen(height, width);
    snake = new Snake(size);
    snake->draw(*screen,1);
    // food = new Food[10];
}

Game::Game(const Game &other) {
    snake = NULL;
    screen = NULL;

    for (int i = 0; i < 10; i++) {
        this->food[i] = other.food[i];
    }

    // this->screen = other.screen;
    // this->snake = other.snake;

    *this = other;
}

Game::~Game() {
    screen->destroy();
    snake->destroy();
    // delete[] food;
}

Game& Game::operator= (const Game &other) {
    snake->destroy();
    screen->destroy();

    this->screen = new Screen();
    this->snake = new Snake();
    
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
    // lastStep é responsável pelo movimento
    // Verificar se lastStep deve ser atualizado (não houve inversão de direção)
    /*if ((lastStepY != (dr*-1) || lastStepY == 0) || (lastStepX != (dc*-1) || lastStepX == 0)) {
        lastStepY = dr;
        lastStepX = dc;
    }*/
    
    if (dr == 1 && dc == 0) {
        if (lastStepY != -1) {
            lastStepY = 1;
            lastStepX = 0;
        } //else if (lastStepY == -1) std::cout << "Inversão\n";
    } else if (dr == -1 && dc == 0) {
        if (lastStepY != 1) {
            lastStepY = -1;
            lastStepX = 0;
        } //else if (lastStepY == 1) std::cout << "Inversão\n";
    } else if (dr == 0 && dc == 1) {
        if (lastStepX != -1) {
            lastStepY = 0;
            lastStepX = 1;
        } //else if (lastStepX == -1) std::cout << "Inversão\n";
    } else if (dr == 0 && dc == -1) {
        if (lastStepX != 1) {
            lastStepY = 0;
            lastStepX = -1;
        } //else if (lastStepX == 1) std::cout << "Inversão\n";
    }

    std::cout << "last = " << lastStepY << "," << lastStepX << "\n";

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
        if (food[i].tempo < 0) screen->set((food[i].posY),(food[i].posX),0);
        else screen->set((food[i].posY),(food[i].posX),2);
    }
}