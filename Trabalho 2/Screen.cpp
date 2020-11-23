#include "Screen.h"
#include <iostream>

Screen::Screen(int height, int width) {
    create();
    this->height = height;
    this->width = width;
    data = new int*[width];
    dataHeight = new int[width];
    for (int i = 0; i < width; i++) {   // Inicialmente não há pixels preenchidos
        data[i] = new int[0];
        dataHeight[i] = 0;
    }
}

Screen::Screen(const Screen &other) {
    create();
    *this = other;
}

Screen::~Screen() {
    destroy();
}

void Screen::create() {
    data = NULL;
    dataHeight = NULL;
}

void Screen::destroy() {
    for (int i = 0; i < width; i++) delete[] data[i];
    delete[] data;
    delete[] dataHeight;
}

int Screen::getWidth() const {
    return width;
}

int Screen::getHeight() const  {
    return height;
}

// r = linha, c = coluna
int Screen::get(int r, int c) const {
    if (r > height || c > width || r < 0 || c < 0) return WALL;

    if (r >= dataHeight[c]) return EMPTY;

    return data[c][r];
}

// r representa a altura da coluna em que será alterado o valor
// O pixel mais alto preenchido é sempre dataHeight[c]-1
void Screen::set(int r, int c, int val) {
    if (dataHeight[c] <= r) {

        // Copiar data[c] antigo antes de realocar
        int auxData[dataHeight[c]], auxHeight = dataHeight[c];
        for (int i = 0; i < dataHeight[c]; i++) auxData[i] = data[c][i];

        dataHeight[c] = r+1;
        delete[] data[c];
        data[c] = new int[(dataHeight[c])]();   // Inicia o array com valor 0  
        for (int i = 0; i < auxHeight; i++) data[c][i] = auxData[i];
    }

    data[c][r] = val;
}

Screen& Screen::operator= (const Screen &other) {
    destroy();

    height = other.height;
    width = other.width;
    data = new int*[other.width];
    dataHeight = new int[other.width];

    for (int i = 0; i < other.width; i++) {
        data[i] = new int[other.dataHeight[i]];
        dataHeight[i] = other.dataHeight[i];
    }

    return *this;
}