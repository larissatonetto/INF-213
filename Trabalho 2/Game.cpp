#include "Game.h"

Game::Game(int height, int width, int size) {
    screen = Screen(height, width);
    snake = Snake(size);
    snake.draw(screen,1);
}

Game::Game(const Game &other) {
    *this = other;
}

Game::~Game() {}

Game& Game::operator= (const Game &other) {
    // Copiando comida
    for (int i = 0; i < 10; i++) {
        food[i] = other.food[i];
    }
    
    // destroy() e create() de snake e screen são chamados dentro de suas classes
    screen = other.screen;
    snake = other.snake;

    return *this;
}

const Screen & Game::getScreen() {
    return screen;
}

int Game::getNumFood() {
    int cont = 0;
    for (int i = 0; i < 10; i++) {
        if (food[i].tempo >= 0) {
            cont++;
        }
    }

    return cont;
}

bool Game::step(int dr, int dc) {    
    // lastStep é responsável pelo movimento
    // Verificar se lastStep deve ser atualizado (não houve inversão de direção)
    if ((dr != 0) && (lastStepY != (dr*-1) || lastStepY == 0)) {
        lastStepY = dr;
        lastStepX = dc;
    } else if ((dc != 0) && (lastStepX != (dc*-1) || lastStepX == 0)) {
        lastStepY = dr;
        lastStepX = dc;
    }

    // Verificando colisão com a parede
    if (snake.head('y')+lastStepY == screen.getHeight() ||
        snake.head('x')+lastStepX == screen.getWidth() ||
        snake.head('y')+lastStepY < 0 ||
        snake.head('x')+lastStepX < 0) {
        snake.draw(screen,1);
        return false;
    }

    // Verificando colisão com o corpo
    if (screen.get(( snake.head('y')+lastStepY ), ( snake.head('x')+lastStepX )) == 1) {
        snake.draw(screen,1);
        return false;
    }
    
    // Atualizando o estado da comida na tela
    foodDown();

    // Verificando se há comida no espaço
    if (screen.get(( snake.head('y')+lastStepY ), ( snake.head('x')+lastStepX )) == 2) {
        snake.draw(screen,0);
        snake.move(lastStepY,lastStepX,true);
        snake.draw(screen,1);

        for (int i = 0; i < 10; i++) {
            if (food[i].posY == snake.head('y') &&
                food[i].posX == snake.head('x'))
                food[i].tempo = -1;
        }

        return true;
    } else {
        snake.draw(screen,0);
        snake.move(lastStepY,lastStepX,false);
        snake.draw(screen,1);
        return true;
    }

    return true;
}

void Game::addFood(int r, int c, int ttl) {
    // Verifica se está sendo inserido fora da tela
    if (r > screen.getHeight() || r < 0 || c > screen.getWidth() || c < 0) return;

    // Verifica se está sendo inserido sobre o corpo da cobra
    if (screen.get(r,c) == 1) return;

    // Verifica se o tempo de comida é válido
    if (ttl <= 0) return;

    // Encontra o primeiro espaço disponível no array de food para armazenar
    for (int i = 0; i < 10; i++) {
        if (food[i].tempo < 0) {
            food[i].posY = r;
            food[i].posX = c;
            food[i].tempo = ttl;

            break;
        }
    }
    drawFood();
}

void Game::foodDown() {
    // Diminui o tempo de vida de todas as comidas no array
    for (int i = 0; i < 10; i++) {
        food[i].tempo-= 1;
    }

    drawFood();
}

void Game::drawFood() {
    for (int i = 0; i < 10; i++) {
        if (food[i].tempo >= 0) {
            // Veririca se o corpo da cobra não está no lugar
            if (screen.get(food[i].posY,food[i].posX) != 1)
                screen.set(food[i].posY,food[i].posX,2);
        } else if (food[i].tempo < 0)   // Apaga a comida caso o tempo seja menor que 0
            if (screen.get(food[i].posY,food[i].posX) != 1)
                screen.set(food[i].posY,food[i].posX,0);
    }
}